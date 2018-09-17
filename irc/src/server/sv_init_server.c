/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_init_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 08:49:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/17 15:03:00 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/types.h>
#include <pwd.h>
//#include <uuid/uuid.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <stdio.h>

static int				sv_sockerr(char *err, int fd)
{
	if (e.verb)
	{
		ft_putstr_fd("\e[31mERROR: ", 2);
		ft_putstr_fd(err, 2);
		ft_putstr_fd("\e[0m\n", 2);
	}
	if (fd >= 0)
		close(fd);
	return (-1);
}

static int				sv_findsocket_v4(struct addrinfo *p, t_env *e)
{
	int					fd;
	int					on;
	socklen_t			len;

	on = 1;
	len = sizeof(e->v4.csin);
	fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
	if (fd < 0)
		return (sv_sockerr("opening stream socket", fd));
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)))
		return (sv_sockerr("setsockopt(SO_REUSEADDR) ", fd));
	if (bind(fd, p->ai_addr, p->ai_addrlen) == -1)
		return (sv_sockerr("binding stream socket", fd));
	if (getsockname(fd, &e->v4.csin, &len))
		ft_putstr((e->verb) ? "(Unable to get IPv4 sockname) " : "");
	if (p->ai_canonname)
		ft_strncpy(e->v4.host, p->ai_canonname, NI_MAXHOST);
	inet_ntop(AF_INET, p->ai_addr, e->v4.addr, sizeof(e->v4.addr));
	return (fd);
}

static int				sv_findsocket_v6(struct addrinfo *p, t_env *e)
{
	int					fd;
	int					on;
	socklen_t			len;

	on = 1;
	len = sizeof(e->v6.csin);
	fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
	if (fd < 0)
		return (sv_sockerr("opening stream socket", fd));
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)))
		return (sv_sockerr("setsockopt(SO_REUSEADDR) ", fd));
	if (setsockopt(fd, IPPROTO_IPV6, IPV6_V6ONLY, &on, sizeof(on)))
		return (sv_sockerr("setsockopt(IPPROTO_IPV6, IPV6_V6ONLY) ", fd));
	if (bind(fd, p->ai_addr, p->ai_addrlen) == -1)
		return (sv_sockerr("binding stream socket", fd));
	if (getsockname(fd, &e->v6.csin, &len))
		ft_putstr((e->verb) ? " (Unable to get IPv6 sockname) " : "");
	if (p->ai_canonname)
		ft_strncpy(e->v6.host, p->ai_canonname, NI_MAXHOST);
	inet_ntop(AF_INET6, p->ai_addr, e->v6.addr, sizeof(e->v6.addr));
	return (fd);
}

static void				sv_getaddrinfo(t_env *e)
{
	struct addrinfo		hints;
	struct addrinfo		*res;
	struct addrinfo		*p;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_PASSIVE | AI_CANONNAME;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	if (getaddrinfo(e->addr, e->port, &hints, &res))
		sv_error("Error: getaddrinfo()", e);
	p = res;
	while (p != NULL)
	{
		if (e->v4.fd < 0 && p->ai_family == AF_INET)
			e->v4.fd = sv_findsocket_v4(p, e);
		if (e->v6.fd < 0 && p->ai_family == AF_INET6)
			e->v6.fd = sv_findsocket_v6(p, e);
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
	if (e->v4.fd >= 0 &&
		listen(e->v4.fd, (e->v6.fd >= 0) ? MAX_CLIENT / 2 : MAX_CLIENT) == -1)
		e->v4.fd = sv_sockerr("listen() on IPv4.", e->v4.fd);
	if (e->verb)
		(e->v4.fd < 0) ? printf("\e[31mUnavailable\e[0m\n") :
			printf("\e[32mAvailable\e[0m %s(%s):%s\n",
					e->v4.host, e->v4.addr, e->port);
	ft_putstr((e->verb) ? "IPv6: " : "");
	if (e->v6.fd >= 0 &&
		listen(e->v6.fd, (e->v4.fd >= 0) ? MAX_CLIENT / 2 : MAX_CLIENT) == -1)
		e->v6.fd = sv_sockerr("listen() on IPv6.", e->v6.fd);
	if (e->verb)
		(e->v6.fd < 0) ? printf("\e[31mUnavailable\e[0m\n") :
			printf("\e[32mAvailable\e[0m %s(%s):%s\n",
					e->v6.host, e->v6.addr, e->port);
}
