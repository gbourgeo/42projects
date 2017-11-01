// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Server.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/11 05:22:35 by root              #+#    #+#             //
//   Updated: 2017/11/01 16:42:53 by root             ###   ########.fr       //
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
	loop(true),
	start_time(time(NULL)),
	nb_clients(0),
	client(),
	ssl(NULL),
	protect(SERV_PWD_PROTECTED),
	passwd(SERV_PWD),
	encrypt(SERV_MSG_ENCRYPTED)
{
	mymemset(&this->client[0], 0, sizeof(t_client) * SERV_MAX_CLIENTS);
	for (int i = 0; i < SERV_MAX_CLIENTS; i++) {
		this->client[i].fd = -1;
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
	if (this->servfd > -1)
		close(this->servfd);
	for (int i = 0; i < SERV_MAX_CLIENTS; i++)
	{
		if (this->client[i].fd > -1)
			Server::clientQuit(this->quitReason.c_str(), this->client[i]);
	}
	ERR_free_strings();
	if (this->mailfd > -1)
		close(this->mailfd);
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
	this->loop = false;
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
	int				i		= 0;
	int				fd;

	fd = accept(this->servfd, &csin, &len);
	if (fd < 0)
		throw DAEMONException("accept");
	
	inet_ntop(AF_INET, &cs->sin_addr.s_addr, this->client[i].addr, 1024);
	getnameinfo(&csin, sizeof(csin), this->client[i].host, NI_MAXHOST, this->client[i].port, NI_MAXSERV, NI_NUMERICSERV);
	i = 0;
	this->client[i].fd = fd;
	if (this->nb_clients >= SERV_MAX_CLIENTS)
		return Server::clientQuit("Server Full", this->client[i]);
	this->tintin->log("INFO", "New connection from %S(%S):%S accepted.",
					  this->client[i].host,
					  this->client[i].addr, this->client[i].port);
	this->client[i].log_time = time(NULL);
	this->client[i].logged = !this->protect;
	this->nb_clients++;
}

void		Server::clientCommands(t_client & cl)
{
	static const char	*name[][100] = SERV_CMDS;
	static void			(Server::*funcs[])(t_client &) = SERV_FUNCS;

	for (int j = 0; name[j][0]; j++) {
		int cmp = mystrcmp(&cl.rd[0], name[j][0]);
		if (cmp == 0 || cmp == ' ') {
			this->tintin->log("INFO", "Request %S.", name[j][0]);
			(this->*funcs[j])(cl);
			return ;
		}
	}
	this->tintin->log("LOG", "%S:%S : %s", cl.host, cl.port, cl.rd);
}

void		Server::clientRead(t_client & cl)
{
	int		ret;
	char	buff[SERV_BUFF];

	ret = recv(cl.fd, buff, SERV_BUFF - 1, 0);
	if (ret <= 0)
		return clientQuit("Connection closed", cl);
	buff[ret] = '\0';
	if (this->encrypt) {
		; //// Decrypt message
	}
	else
		cl.rd += buff;

	std::size_t found;
	while ((found = cl.rd.find_first_of('\n')) != std::string::npos)
	{
		cl.rd.at(found) = 0;
		if (!cl.logged)
		{
			if (mystrcmp(cl.rd.c_str(), this->passwd.c_str()) != 0)
				return Server::clientQuit("Wrong password", cl);
			cl.logged = true;
		}
		else
			Server::clientCommands(cl);
		cl.rd = cl.rd.substr(found + 1);
	}
}

void		Server::clientWrite(t_client &cl)
{
	int		ret;

	if (cl.wr.size() > 0)
	{
		if (this->encrypt) {
			; //// Crypt message
		}
		ret = write(cl.fd, cl.wr.c_str(), cl.wr.size());
		if (ret < 0)
			return Server::clientQuit("Connection closed", cl);
		cl.wr = cl.wr.substr(ret);
	}
}

void		Server::clientQuit(const char *reason, t_client &cl)
{
	std::string	info("Matt_daemon: \n");

	info.insert(info.size() - 1, reason);
	cl.wr += info;
	Server::clientWrite(cl);
	this->tintin->log("INFO", "%S(%S):%S disconnected (%S).",
					  cl.host, cl.addr, cl.port, reason);
	close(cl.fd);
	mymemset(&cl, 0, sizeof(t_client));
	cl.fd = -1;
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
	this->tintin->log("INFO", "Started on %S", ctime(&this->start_time));
	this->tintin->log("INFO", "Request clearlogs.");
	cl.wr += "Logs cleared !\n";
}

void		Server::setDaemonPwd(t_client & cl)
{
	size_t	found;

	if ((found = cl.rd.find_first_of(' ')) == std::string::npos)
	{
		if (this->protect == true) {
			this->tintin->log("INFO", "Daemon protection disabled.");
			cl.wr += "Daemon protection disabled.\n";
			this->protect = false;
			this->passwd.clear();
		}
	}
	else
	{
		if (this->protect == false) {
			this->tintin->log("INFO", "Daemon protection enabled.");
			cl.wr += "Daemon protection enabled.\n";
			this->protect = true;
			this->passwd = cl.rd.substr(found + 1);
		}
	}
}

void		Server::quit(t_client &cl)
{
	(void)cl;
	this->quitReason += "Request quit received";
	this->loop = false;
}
