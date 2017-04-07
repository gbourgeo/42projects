/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_init_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 08:49:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/07 14:32:21 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <stdio.h>

static int			sv_sockerr(char *err, int fd)
{
	if (e.verb)
	{
		ft_putstr_fd("\e[31mERROR: ", 2);
		ft_putstr_fd(err, 2);
		ft_putstr_fd("\e[0m\n", 2);
	}
	if (fd >= 0)
		close(fd);
	fd = -1;
	return (-1);
}

static void				sv_sockavail(t_env *e, int isv6)
{
	socklen_t			len;

	len = sizeof(struct sockaddr);
	if (isv6)
	{
		inet_ntop(AF_INET6, V6ADDR(&e->v6.csin), e->v6.addr, sizeof(e->v6.addr));
		getnameinfo(&e->v6.csin, len, e->v6.host, NI_MAXHOST, e->v6.port,
					NI_MAXHOST, NI_NUMERICSERV);
		printf("\e[32mAvailable\e[0m %s(%s) %s\n",
				e->v6.host, e->v6.addr, e->v6.port);
		return ;
	}
	inet_ntop(AF_INET, V4ADDR(&e->v4.csin), e->v4.addr, sizeof(e->v4.addr));
	getnameinfo(&e->v4.csin, len, e->v4.host, NI_MAXHOST, e->v4.port,
				NI_MAXHOST, NI_NUMERICSERV);
		printf("\e[32mAvailable\e[0m %s(%s) %s\n",
				e->v4.host, e->v4.addr, e->v4.port);
}

static int				sv_findsocket(struct addrinfo *p, int ip)
{
	int					fd;
	int					on;

	on = 1;
	ft_memcpy((!ip) ? &e.v4.csin : &e.v6.csin, p->ai_addr, sizeof(e.v4.csin));
	fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
	if (fd < 0)
		return (sv_sockerr("opening stream socket", fd));
	if (!setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)))
	{
		if (!ip || !setsockopt(fd, IPPROTO_IPV6, IPV6_V6ONLY, &on, sizeof(on)))
		{
			if (bind(fd, p->ai_addr, p->ai_addrlen) != -1)
				return (fd);
			return (sv_sockerr("binding stream socket", fd));
		}
		return (sv_sockerr("setsockopt(IPPROTO_IPV6, IPV6_V6ONLY) ", fd));
	}
	return (sv_sockerr("setsockopt(SO_REUSEADDR) ", fd));
}

static void				sv_getaddrinfo(t_env *e)
{
	struct addrinfo		hints;
	struct addrinfo		*res;
	struct addrinfo		*p;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	if (getaddrinfo(e->name, e->port, &hints, &res))
		sv_error("Error: getaddrinfo()", e);
	p = res;
	while (p != NULL)
	{
		if (e->v4.fd < 0 && p->ai_family == AF_INET)
			e->v4.fd = sv_findsocket(p, 0);
		if (e->v6.fd < 0 && p->ai_family == AF_INET6)
			e->v6.fd = sv_findsocket(p, 1);
		if (e->v4.fd != -1 && e->v6.fd != -1)
			break ;
		p = p->ai_next;
	}
	freeaddrinfo(res);
	if (p == NULL && e->v4.fd < 0 && e->v6.fd < 0)
		sv_error("Error: Invalid or Unavailable port.", e);
}

void					sv_init_server(t_env *e)
{
	e->v4.fd = -1;
	e->v6.fd = -1;
	sv_getaddrinfo(e);
	ft_putstr((e->verb) ? "IPv4: " : "");
	sv_sockavail(e, 0);
	if (e->v4.fd >= 0 &&
		listen(e->v4.fd, (e->v6.fd >= 0) ? MAX_CLIENT / 2 : MAX_CLIENT) == -1)
		e->v4.fd = sv_sockerr("listen() on IPv4.", e->v4.fd);
	else if (e->verb)
		printf("\e[32mAvailable\e[0m %s(%s) %s\n",
				e->v4.host, e->v4.addr, e->v4.port);
	ft_putstr((e->verb) ? "IPv6: " : "");
	sv_sockavail(e, 1);
	if (e->v6.fd >= 0 &&
		listen(e->v6.fd, (e->v4.fd >= 0) ? MAX_CLIENT / 2 : MAX_CLIENT) == -1)
		e->v6.fd = sv_sockerr("listen() on IPv6.", e->v6.fd);
	else if (e->verb)
		printf("\e[32mAvailable\e[0m %s(%s) %s\n",
				e->v6.host, e->v6.addr, e->v6.port);
	if (!*e->name)
		gethostname(e->name, SERVER_LEN);
}
