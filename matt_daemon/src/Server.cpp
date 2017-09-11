// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Server.cpp                                         :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/09/11 05:22:35 by root              #+#    #+#             //
//   Updated: 2017/09/11 06:16:05 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Server.hpp"
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

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
	servfd = -1;
	err = NULL;
	if (getaddrinfo(SERV_ADDR, SERV_PORT, &hints, &res))
	{
		err = "Getaddrinfo failed.";
		return ;
	}
	p = res;
	while (p != NULL)
	{
		if (servfd < 0 && p->ai_family == AF_INET)
			servfd = findSocket(p);
		if (servfd != -1)
			break ;
		p = p->ai_next;
	}
	freeaddrinfo(res);
	if (p == NULL || servfd < 0)
		err = "Invalid address or unavailable port";
	else if (listen(servfd, SERV_CLIENTS) == -1)
		err = "Listen failed.";
}

Server::Server(Server const & src)
{
	*this = src;
}

Server::~Server(void)
{
	if (servfd != -1)
		close(servfd);
}

Server & Server::operator=(Server const & rhs)
{
	(void)rhs;
	return *this;
}

int Server::findSocket(struct addrinfo *p)
{
	int			on;

	on = 1;
	servfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
	if (servfd < 0)
		return -1;
	if (setsockopt(servfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)))
	{
		close(servfd);
		return -1;
	}
	if (bind(servfd, p->ai_addr, p->ai_addrlen) == -1)
	{
		close(servfd);
		return -1;
	}
	return (servfd);
}

int	Server::getServfd(void) const
{
	return servfd;
}

const char *Server::getError(void) const
{
	return err;
}
