// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   getSocket.cpp                                      :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: root </var/mail/root>                      +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2017/10/15 14:00:37 by root              #+#    #+#             //
//   Updated: 2017/11/01 12:51:58 by root             ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "Server.hpp"
#include "Exceptions.hpp"
#include "stdlib_func.hpp"
#include <string.h>
#include <unistd.h>

static const char	*strconcat(const char *dst, const char *s1, const char *s2)
{
	mymemset(dst, 0, 100);
	mystrcpy(dst, s1);
	mystrcat(dst, ":");
	mystrcat(dst, s2);
	return dst;
}

int			servSocket(struct addrinfo *p)
{
	int		fd;
	int		on;

	on = 1;
	fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
	if (fd < 0)
		return -1;
	if (!setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) &&
		!bind(fd, p->ai_addr, p->ai_addrlen) &&
		!listen(fd, SERV_MAX_CLIENTS))
		return fd;
	close(fd);
	return -1;
}

int			mailSocket(struct addrinfo *p)
{
	int		fd;

	fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
	if (fd < 0)
		return -1;
	if (!connect(fd, p->ai_addr, p->ai_addrlen))
		return fd;
	close(fd);
	return -1;
}

int			getSocket(const char *addr, const char *port, int (*func)(addrinfo *))
{
	int				fd;
	struct addrinfo	hints;
	struct addrinfo	*res;
	struct addrinfo	*p;
	const char		err[100] = {0};

	fd = -1;
	mymemset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_PASSIVE | AI_CANONNAME;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	if (getaddrinfo(addr, port, &hints, &res))
		throw DAEMONException(strconcat(err, addr, port));
	p = res;
	while (p != NULL)
	{
		if (p->ai_family == AF_INET)
			fd = (*func)(p);
		if (fd >= 0)
			break ;
		p = p->ai_next;
	}
	freeaddrinfo(res);
	if (p == NULL || fd < 0)
		throw DAEMONException(strconcat(err, addr, port));
	return fd;
}
