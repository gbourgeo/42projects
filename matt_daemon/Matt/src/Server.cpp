// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Server.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/11 05:22:35 by root              #+#    #+#             //
//   Updated: 2018/09/15 17:17:31 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Server.hpp"
#include "Exceptions.hpp"
#include "getSocket.hpp"
#include "stdlib_func.hpp"
#include <fstream>
#include <unistd.h>
#include <arpa/inet.h>

Server::Server(void):
	tintin(NULL),
	servfd(getSocket(SERV_ADDR, SERV_PORT, &servSocket)),
	mailfd(-1),
	fdr({0}),
	fdw({0}),
	loop(true),
	start_time(time(NULL)),
	nb_clients(0),
	client(),
	ctx(),
	ssl(NULL),
	protect(SERV_PASS_PROTECTD),
	passwd(SERV_PASSWD),
	encrypt(SERV_MSG_ENCRYPTED)
{
	for (int i = 0; i < SERV_MAX_CLIENTS + 1; i++) {
		Server::clearClient(this->client[i]);
	}

	const SSL_METHOD	*method;

	if (SSL_library_init() < 0)
		throw DAEMONException("OpenSSL not initialized");
	OpenSSL_add_ssl_algorithms();
	OpenSSL_add_all_algorithms();
	SSL_load_error_strings();
	ERR_load_crypto_strings();
	method = SSLv23_client_method();
	if ((this->ctx = SSL_CTX_new(method)) == NULL) {
		std::string err = std::string("OpenSSL context not initialized: ");
		err += std::string(ERR_error_string(ERR_get_error(), NULL));
		throw DAEMONException(&err[0]);
	}
	SSL_CTX_set_options(this->ctx, SSL_OP_NO_SSLv2);
}

Server::Server(Server const & src)
{
	*this = src;
}

Server::~Server(void)
{
	if (this->quitReason.size() > 0) {
		Server::log("INFO", this->quitReason.c_str());
		for (int i = 0; i < SERV_MAX_CLIENTS; i++)
		{
			if (this->client[i].fd > -1)
				Server::clientQuit(this->quitReason.c_str(), this->client[i]);
		}
	}
	if (this->servfd > -1)
		close(this->servfd);
	if (this->mailfd > -1)
		close(this->mailfd);
	ERR_free_strings();
	if (this->ssl)
	{
		SSL_shutdown(this->ssl);
		SSL_shutdown(this->ssl);
		SSL_clear(this->ssl);
		SSL_free(this->ssl);
		this->ssl = NULL;
	}
	if (this->ctx) {
		SSL_CTX_free(this->ctx);
		this->ctx = NULL;
	}
}

Server & Server::operator=(Server const & rhs)
{
	(void)rhs;
	return *this;
}

void		Server::setReporter(Tintin_reporter *reporter)
{
	this->tintin = reporter;
}

void		Server::clearClient( t_client & cl )
{
	cl.fd = -1;
	mymemset(cl.addr, 0, sizeof(cl.addr));
	mymemset(cl.host, 0, sizeof(cl.host));
	mymemset(cl.port, 0, sizeof(cl.port));
	cl.log_time = 0;
	cl.logged = false;
	cl.rd = "";
	cl.wr = "";
	cl.wr_encoded = "";
}

void		Server::log(const std::string & title, const std::string & info, ...)
{
	va_list		args;

	if (!this->tintin)
		return ;
	va_start(args, info);
	this->tintin->log(title, info, args);
	va_end(args);
}

int			Server::setupSelect(void)
{
	int		i;
	int		max;

	FD_ZERO(&this->fdr);
	FD_ZERO(&this->fdw);
	FD_SET(this->servfd, &this->fdr);
	max = this->servfd;
	i = 0;
	while (i < SERV_MAX_CLIENTS)
	{
		if (this->client[i].fd > max)
			max = this->client[i].fd;
		if (this->client[i].fd > -1) {
			FD_SET(this->client[i].fd, &this->fdr);
			FD_SET(this->client[i].fd, &this->fdw);
		}
		i++;
	}
	return max;
}

void		Server::acceptConnections(void)
{
	struct sockaddr	csin;
	struct sockaddr_in *cs	= (struct sockaddr_in *)&csin;
	socklen_t		len		= sizeof(csin);
	int				i;
	int				fd;

	fd = accept(this->servfd, &csin, &len);
	if (fd < 0)
		throw DAEMONException("accept");

	i = this->nb_clients++;
	this->client[i].fd = fd;
	inet_ntop(AF_INET, &cs->sin_addr.s_addr, this->client[i].addr, 1024);
	getnameinfo(&csin, sizeof(csin), this->client[i].host, NI_MAXHOST, this->client[i].port, NI_MAXSERV, NI_NUMERICSERV);
	if (this->nb_clients > SERV_MAX_CLIENTS)
		return Server::clientQuit("Server Full", this->client[i]);
	this->client[i].log_time = time(NULL);
	this->client[i].logged = !this->protect;
	if (this->protect)
		this->client[i].wr = "Pass: ";
	else
		this->client[i].wr = "Welcome stranger.\n";
	Server::log("INFO", "New connection from %s(%s):%s accepted.",
					  this->client[i].host,
					  this->client[i].addr, this->client[i].port);
}

void		Server::clientCommands(t_client & cl)
{
	static const char		*name[][100] = SERV_CMDS;
	static void				(Server::*funcs[])(t_client &) = SERV_FUNCS;
	std::vector<std::string> cmd = Server::split(cl.rd, ' ');

	for (int j = 0; name[j][0]; j++) {
		int comp = mystrcmp(cmd.front().c_str(), name[j][0]);
		if (comp == 0) {
			Server::log("INFO", "Request %s.", name[j][0]);
			(this->*funcs[j])(cl);
			return ;
		}
	}
	Server::log("LOG", "%s:%s : %s", cl.host, cl.port, cl.rd.c_str());
}

void		Server::clientRead( t_client & cl )
{
	int		ret;
	t_hdr	data;

	if (this->encrypt) {
		ret = recv(cl.fd, &data, sizeof(data), 0);
		if (ret <= 0)
			return clientQuit("Client closed connection", cl);
		if (data.magic != DAEMON_MAGIC)
			return Server::log("INFO", "%s:%s : Wrong message header magic.",
									 cl.host, cl.port);
		if (data.crypted)
			return Server::log("INFO", "%s:%s : Data not crypted.",
									 cl.host, cl.port);
		cl.rd += std::string(data.data, ret - (sizeof(data) - sizeof(data.data)));
		if (data.datalen > cl.rd.size())
			return ;
		char *msg = new char[Base64decode_len(cl.rd.c_str()) + 1];
		Base64decode(msg, cl.rd.c_str());
		cl.rd.clear();
		cl.rd = std::string(msg);
		delete [] msg;
	}
	else
	{
		ret = recv(cl.fd, &data.data, sizeof(data.data) - 1, 0);
		if (ret <= 0)
			return clientQuit("Client closed connection", cl);
		cl.rd += std::string(data.data, ret);
	}

	std::size_t found;
	while ((found = cl.rd.find_first_of('\n')) != std::string::npos)
	{
		cl.rd.at(found) = '\0';
		if (!cl.logged) {
			if (mystrcmp(cl.rd.c_str(), this->passwd.c_str()) != 0)
				return Server::clientQuit("Wrong password", cl);
			cl.wr += "Welcome stranger.\n";
			cl.logged = true;
		}
		else if (found)
			Server::clientCommands(cl);
		cl.rd = cl.rd.substr(found + 1);
	}
}

void		Server::clientWrite( t_client &cl )
{
	int			ret;
	t_hdr		msg;

	if (this->encrypt && cl.wr.size() > 0)
	{
		char	*encode = new char[Base64encode_len(cl.wr.size())];
		Base64encode(encode, cl.wr.c_str(), cl.wr.size());
		cl.wr_encoded += encode;
		delete [] encode;
		cl.wr.clear();
	}

	std::string &data = (this->encrypt) ? cl.wr_encoded : cl.wr;
	if (data.size() > 0)
	{
		msg.magic = DAEMON_MAGIC;
		msg.crypted = !this->encrypt;
		msg.datalen = data.size();
		mystrncpy(msg.data, data.c_str(), DAEMON_BUFF - 1);
		ret = send(cl.fd, &msg, sizeof(msg), 0);
		if (ret <= 0)
			return Server::clientQuit("Client closed connection", cl);
		data = data.substr(mystrlen(msg.data));
	}
}

void		Server::clientQuit(const char *reason, t_client &cl)
{
	std::string	info("Matt_daemon: ");

	if (reason) {
		info.append(reason);
		cl.wr = info + "\n";
		Server::clientWrite(cl);
		Server::log("INFO", "%s(%s):%s disconnected (%s).",
					cl.host, cl.addr, cl.port, reason);
	}
	close(cl.fd);
	Server::clearClient(cl);
	this->nb_clients--;
}

void		Server::launchServer(void)
{
	int		maxfd;
	int		ret;
	struct timeval timeout;

	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	while (this->loop)
	{
		maxfd = Server::setupSelect();
		ret = select(maxfd + 1, &this->fdr, &this->fdw, NULL, &timeout);
		if (ret == -1)
			throw DAEMONException("select");
		else if (ret > 0)
		{
			if (FD_ISSET(this->servfd, &this->fdr))
				Server::acceptConnections();
			for (int i = 0; i < SERV_MAX_CLIENTS; i++) {
				if (this->client[i].fd > -1) {
					if (FD_ISSET(this->client[i].fd, &this->fdr))
						Server::clientRead(this->client[i]);
					if (FD_ISSET(this->client[i].fd, &this->fdw))
						Server::clientWrite(this->client[i]);
				}
			}
		}
	}
}

void		Server::mailMeDaemonInfo( void )
{
	t_client	me;

	me.rd = "mail all";
	Server::sendMail(me);
}

void		Server::clearDaemonLogs(t_client &cl)
{
	this->tintin->clearLogs();
	Server::log("INFO", "Started on %s", ctime(&this->start_time));
	Server::log("INFO", "Request clearlogs.");
	cl.wr += "Logs cleared !\n";
}

void		Server::setDaemonPasswd(t_client & cl)
{
	std::string		msg("Daemon protection ");
	std::vector<std::string> cmd;

	cmd = Server::split(cl.rd, ' ');
	if (cmd.size() > 1)
	{
		if (this->protect == false) {
			msg += "enabled.";
			Server::log("INFO", "%s", msg.c_str());
			this->protect = true;
			this->passwd = std::string(cmd.at(1));
			Server::sendAllClients(msg);
		}
	}
	else
	{
		if (this->protect == true) {
			msg += "disabled.";
			Server::log("INFO", "%s", msg.c_str());
			this->protect = false;
			this->passwd.clear();
			Server::sendAllClients(msg);
		}
	}
}

void		Server::setDaemonCrypted(t_client & cl)
{
	std::string		msg("Daemon encryption ");

	this->encrypt = !this->encrypt;
	msg += (this->encrypt) ? "enabled." : "disabled.";
	Server::log("INFO", "%s", msg.c_str());
	Server::sendAllClients(msg);
	(void)cl;
}

void		Server::sendAllClients(std::string & msg)
{
	msg += "\n";
	for (int i = 0; i < SERV_MAX_CLIENTS; i++) {
		if (this->client[i].fd > -1) {
			this->client[i].wr += msg;
		}
	}
}
		
void		Server::quit(t_client &cl)
{
	std::string msg = "Matt_daemon: Request quit received.\n";

	for (int i = 0; i < SERV_MAX_CLIENTS; i++) {
		if (this->client[i].fd > -1) {
			this->client[i].wr += msg;
			Server::clientWrite(this->client[i]);
		}
	}	
	this->loop = false;
	(void)cl;
}

const std::vector<std::string> Server::split(const std::string &str, const char &c)
{
	std::string		buff("");
	std::vector<std::string>	ret;

	for (auto n:str)
	{
		if (n == c && buff != "")
		{
			ret.push_back(buff);
			buff = "";
		}
		else
			buff += n;
	}
	if (buff != "")
		ret.push_back(buff);
	return ret;
}
