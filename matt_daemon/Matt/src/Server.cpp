// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Server.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/11 05:22:35 by root              #+#    #+#             //
//   Updated: 2017/10/21 21:09:42 by root             ###   ########.fr       //
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
	encrypt(SERV_ENCRYPT),
	protect(SERV_PROTECT),
	client(),
	ssl(NULL)
{
	mymemset(&this->client[0], 0, sizeof(t_client) * SERV_CLIENTS);
	for (int i = 0; i < SERV_CLIENTS; i++) {
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
	for (int i = 0; i < SERV_CLIENTS; i++)
	{
		if (this->client[i].fd != -1)
			close(this->client[i].fd);
	}
	ERR_free_strings();
	if (this->mailfd)
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

void		Server::checkClientLogged(void)
{
	for (int i = 0; i < SERV_CLIENTS; i++) {
		if (this->client[i].fd > -1 && !this->client[i].logged) {
			time_t timer = time(NULL);
			if (timer - this->client[i].log_time > SERV_LOGGIN_TIME) {
				write(this->client[i].fd, "Loggin' timeout.\n", 17);
				close(this->client[i].fd);
				mymemset(&this->client[i].fd, 0, sizeof(t_client));
				this->client[i].fd = -1;
			}
		}
	}
}

int			Server::setupSelect(void)
{
	int		i;
	int		max;

	FD_ZERO(&this->fdr);
	FD_SET(this->servfd, &this->fdr);
	max = this->servfd;
	i = 0;
	while (i < SERV_CLIENTS)
	{
		if (this->client[i].fd > max)
			max = this->client[i].fd;
		if (this->client[i].fd > -1)
			FD_SET(this->client[i].fd, &this->fdr);
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
	while (i < SERV_CLIENTS && this->client[i].fd != -1)
		i++;
	if (i < SERV_CLIENTS) {
		this->tintin->log("INFO", "New connection from %S(%S):%S accepted.",
						  this->client[i].host,
						  this->client[i].addr, this->client[i].port);
		this->client[i].fd = fd;
		this->client[i].log_time = time(NULL);
		this->nb_clients++;
	}
	else {
		this->tintin->log("INFO", "New connection from %S(%S):%S rejected.",
						  this->client[i].host,
						  this->client[i].addr, this->client[i].port);
		write(fd, "Server full.\n", 13);
		close(fd);
	}
}

void		Server::clientCommands(t_client & cl)
{
	static const char	*name[] = SERV_CMDS;
	static void			(Server::*funcs[])(t_client &) = SERV_FUNCS;
	int					j;
	int					cmp;

	for (j = 0; name[j]; j++) {
		cmp = mystrcmp(&cl.cmd[0], name[j]);
		if (cmp == 0 || cmp == ' ') {
			this->tintin->log("INFO", "Request %S.", name[j]);
			(this->*funcs[j])(cl);
			return ;
		}
	}
	this->tintin->log("LOG", "%S:%S : %s", cl.host, cl.port, cl.cmd);
}

void		Server::clientRead(t_client & cl)
{
	int		ret;
	char	buff[SERV_BUFF];

	ret = recv(cl.fd, buff, SERV_BUFF - 1, 0);
	if (ret <= 0)
	{
		this->tintin->log("INFO", "%S(%S):%S has disconnected.",
							cl.host, cl.addr, cl.port);
		close(cl.fd);
		mymemset(&cl, 0, sizeof(t_client));
		cl.fd = -1;
		this->nb_clients--;
		return ;
	}
	buff[ret] = '\0';
	cl.cmd += buff;

	std::size_t found;
	while ((found = cl.cmd.find_first_of('\n')) != std::string::npos)
	{
		cl.cmd.at(found) = 0;
		if (this->protect && !cl.logged) {
			;
		} else
			clientCommands(cl);
		cl.cmd = cl.cmd.substr(found + 1);
	}
}

void		Server::loopServ(void)
{
	int		maxfd;
	int		ret;
	struct timeval timeout;

	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	while (this->loop)
	{
		if (this->protect)
			Server::checkClientLogged();
		maxfd = Server::setupSelect();
		ret = select(maxfd + 1, &this->fdr, NULL, NULL, &timeout);
		if (ret == -1)
			throw DAEMONException("select");
		else if (ret > 0)
		{
			if (FD_ISSET(this->servfd, &this->fdr))
				acceptConnections();
			for (int i = 0; i < SERV_CLIENTS; i++) {
				if (this->client[i].fd > -1 &&
					FD_ISSET(this->client[i].fd, &this->fdr))
					clientRead(this->client[i]);
			}
		}
	}
}

void		Server::clearDaemonLogs(t_client &cl)
{
	(void)cl;
	this->tintin->clearLogs();
	this->tintin->log("INFO", "Started on %S", ctime(&this->start_time));
	this->tintin->log("INFO", "Request clearlogs.");
}

void		Server::quit(t_client &cl)
{
	(void)cl;
	for (int i = 0; i < SERV_CLIENTS; i++)
		write(this->client[i].fd, "Request quit received.\n", 23);
	this->loop = false;
}
