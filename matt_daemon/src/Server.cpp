// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Server.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/11 05:22:35 by root              #+#    #+#             //
//   Updated: 2017/09/24 09:49:18 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Server.hpp"
#include "Exceptions.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>

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
	memset(this->cl, -1, SERV_CLIENTS * sizeof(int));
	this->loop = true;
}

Server::Server(Server const & src)
{
	*this = src;
}

Server::~Server(void)
{
	int	i;

	if (this->servfd != -1)
		close(this->servfd);
	i = 0;
	while (i < 3)
	{
		if (this->cl[i] != -1)
			close(this->cl[i]);
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
			acceptConnections();
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
		if (this->cl[i] > max)
			max = this->cl[i];
		if (this->cl[i] != -1)
			FD_SET(this->cl[i], &this->fdr);
		i++;
	}
	return max;
}

void		Server::acceptConnections(void)
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
	while (i < 3 && this->cl[i] != -1)
		i++;
	if (i == 3)
		close(fd);
	else
		this->cl[i] = fd;
	// Recuperer les infos du client et les mettre dans le fichier log ??
}

void		Server::clientRead(Tintin_reporter *tintin)
{
	int		i;
	int		ret;
	char	buff[513];

	i = 0;
	while (i < SERV_CLIENTS)
	{
		if (this->cl[i] >= 0 && FD_ISSET(this->cl[i], &this->fdr))
		{
			ret = recv(this->cl[i], buff, 512, 0);
			if (ret <= 0)
			{
				close(this->cl[i]);
				this->cl[i] = -1;
				return ;
			}
			buff[ret - 1] = '\0';
			if (Server::mystrcmp(buff, "quit") == 0)
			{
				tintin->log("INFO", "Request quit.");
				this->loop = false;
			}
			else if (buff[0])
				tintin->log("LOG", "User input", buff);
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
