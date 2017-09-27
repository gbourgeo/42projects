// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Server.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/11 05:22:35 by root              #+#    #+#             //
//   Updated: 2017/09/27 16:21:39 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Server.hpp"
#include "Exceptions.hpp"
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

Server::Server(void)
{
	struct addrinfo	hints;
	struct addrinfo	*res;
	struct addrinfo	*p;

	memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_PASSIVE | AI_CANONNAME;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	this->servfd = -1;
	if (getaddrinfo(SERV_ADDR, SERV_PORT, &hints, &res))
		throw DAEMONException("Unable to resolve the server address.");
	p = res;
	while (p != NULL)
	{
		if (this->servfd < 0 && p->ai_family == AF_INET)
			this->servfd = Server::findSocket(p);
		if (this->servfd != -1)
			break ;
		p = p->ai_next;
	}
	freeaddrinfo(res);
	if (p == NULL || this->servfd < 0)
	{
		errno = 0;
		throw DAEMONException("Invalid address o/ Unavailable port");
	}
	if (listen(this->servfd, SERV_CLIENTS) == -1)
		throw DAEMONException("listen");
	for (int i = 0; i < SERV_CLIENTS; i++) {
		this->client[i].fd = -1;
		memset(this->client[i].addr, 0, sizeof(this->client[i].addr));
		memset(this->client[i].host, 0, sizeof(this->client[i].addr));
		memset(this->client[i].port, 0, sizeof(this->client[i].addr));
	}
	this->loop = true;
}

Server::Server(Server const & src)
{
	*this = src;
}

Server::~Server(void)
{
	if (this->servfd != -1)
		::close(this->servfd);
	for (int i = 0; i < SERV_CLIENTS; i++)
	{
		if (this->client[i].fd != -1)
			::close(this->client[i].fd);
		i++;
	}
}

Server & Server::operator=(Server const & rhs)
{
	(void)rhs;
	return *this;
}

void		Server::loopServ(Tintin_reporter *tintin)
{
	int		maxfd;
	int		ret;

	while (this->loop)
	{
		maxfd = Server::setupSelect();
		ret = select(maxfd + 1, &this->fdr, NULL, NULL, NULL);
		if (ret == -1)
			throw DAEMONException("select");
		if (FD_ISSET(this->servfd, &this->fdr))
			acceptConnections(tintin);
		else
			clientRead(tintin);
	}
}

void		Server::quit(void)
{
	this->loop = false;
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
		if (this->client[i].fd != -1)
			FD_SET(this->client[i].fd, &this->fdr);
		i++;
	}
	return max;
}

void		Server::acceptConnections(Tintin_reporter *tintin)
{
	int				fd;
	struct sockaddr	csin;
	socklen_t		len;
	int				i;

	len = sizeof(csin);
	fd = accept(this->servfd, &csin, &len);
	if (fd < 0)
		throw DAEMONException("accept");
	i = 0;
	while (i < SERV_CLIENTS && this->client[i].fd != -1)
		i++;
	if (i >= SERV_CLIENTS)
	{
		close(fd);
		return ;
	}
	this->client[i].fd = fd;

	struct sockaddr_in *cs = (struct sockaddr_in *)&csin;
	
	inet_ntop(AF_INET, &cs->sin_addr.s_addr, this->client[i].addr, 1024);
	// getnameinfo(&csin, sizeof(csin), host, NI_MAXHOST, port, NI_MAXSERV, NI_NUMERICSERV);
	// strncpy(this->client[i].host, host, NI_MAXHOST);
	// strncpy(this->client[i].port, port, NI_MAXSERV);
	// tintin->log("INFO", "New connection from ", this->client[i].addr,
				// this->client[i].host, this->client[i].port);
	tintin->log("INFO", "New client from ", this->client[i].addr);
}

void		Server::clientRead(Tintin_reporter *tintin)
{
	int		i;
	int		ret;
	char	buff[513];

	i = 0;
	while (i < SERV_CLIENTS)
	{
		if (this->client[i].fd != -1 && FD_ISSET(this->client[i].fd, &this->fdr))
		{
			ret = recv(this->client[i].fd, buff, 512, 0);
			if (ret <= 0)
			{
				tintin->log("INFO", this->client[i].addr, "disconnected.");
				close(this->client[i].fd);
				this->client[i].fd = -1;
				return ;
			}
			if (buff[ret - 1] == '\n')
				buff[ret - 1] = '\0';
			if (Server::mystrcmp(buff, "quit") == 0)
			{
				tintin->log("INFO", "Request quit from ",
							this->client[i].addr);
							// this->client[i].addr,
							// this->client[i].port);
				this->loop = false;
			}
			else if (buff[0])
//				tintin->log("LOG", "User input", buff);
				tintin->log("LOG", "User input", this->client[i].addr, " ", buff);
		}
		i++;
	}
}

int			Server::findSocket(struct addrinfo *p)
{
	int		fd;
	int		on;

	on = 1;
	fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
	if (fd < 0)
		return -1;
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)))
	{
		close(fd);
		return -1;
	}
	if (bind(fd, p->ai_addr, p->ai_addrlen) == -1)
	{
		close(fd);
		return -1;
	}
	return fd;
}

int			Server::mystrcmp(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	if (!s1 || !s2)
		return 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return s1[i] - s2[i];
}
