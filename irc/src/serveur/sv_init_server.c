/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_init_server.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 08:49:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/11/08 19:35:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#include <stdio.h>

static int				sv_sockerr(char *err, int fd)
{
	ft_putstr_fd("\e[31mERROR: ", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd("\e[0m\n", 2);
	if (fd >= 0)
		close(fd);
	return (-1);
}

static int				sv_sockavail(t_env *e, int isv6)
{
	struct sockaddr_in	s4;
	struct sockaddr_in6	s6;
	socklen_t			len;

	len = (isv6) ? sizeof(s6) : sizeof(s4);
	if ((isv6 && getsockname(e->ipv6, (struct sockaddr *)&s6, &len)) ||
		(!isv6 && getsockname(e->ipv4, (struct sockaddr *)&s4, &len)))
		return (sv_sockerr("getsockname failed.", (isv6) ? e->ipv6 : e->ipv4));
	ft_putstr("\e[32mAvailable\e[0m ");
	if (isv6)
		inet_ntop(AF_INET6, &s6.sin6_addr.s6_addr, e->addr6, sizeof(e->addr6));
	else
		inet_ntop(AF_INET, &s4.sin_addr.s_addr, e->addr4, sizeof(e->addr4));
	return ((isv6) ? e->ipv6 : e->ipv4);
}

static int				sv_findsocket(struct addrinfo *p, int ip)
{
	int					fd;
	int					on;

	on = 1;
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
		return (sv_sockerr("setsockopt(IPPROTO_IPV6, IPV6_ONLY) ", fd));
	}
	return (sv_sockerr("setsockopt(SO_REUSEADDR) ", fd));
}

static void				sv_getaddrinfo(char *port, t_env *e)
{
	struct addrinfo		hints;
	struct addrinfo		*res;
	struct addrinfo		*p;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	if (getaddrinfo(NULL, port, &hints, &res))
		sv_error("Error: getaddrinfo()", e);
	p = res;
	while (p != NULL)
	{
		if (e->ipv4 < 0 && p->ai_family == AF_INET)
			e->ipv4 = sv_findsocket(p, 0);
		if (e->ipv6 < 0 && p->ai_family == AF_INET6)
			e->ipv6 = sv_findsocket(p, 1);
		if (e->ipv4 != -1 && e->ipv6 != -1)
			break ;
		p = p->ai_next;
	}
	freeaddrinfo(res);
	if (p == NULL && e->ipv4 < 0 && e->ipv6 < 0)
		sv_error("Error: Invalid or Unavailable port.", e);
}

void					sv_init_server(char **av, t_env *e)
{
	char				*port;
	struct passwd		*p;

	port = (*av[1] != '-') ? av[1] : av[2];
	p = getpwuid(getuid());
	ft_strncpy(e->name, (p) ? p->pw_name : "unknown", sizeof(e->name));
	e->ipv4 = -1;
	e->ipv6 = -1;
	sv_getaddrinfo(port, e);
	ft_putstr("IPV4: ");
	if (sv_sockavail(e, 0) != -1)
		printf("%s %s\n", e->addr4, port);
	ft_putstr("IPV6: ");
	if (sv_sockavail(e, 1) != -1)
		printf("%s %s\n", e->addr6, port);
	if (e->ipv4 >= 0 && listen(e->ipv4, MAX_CLIENT) == -1)
		sv_error("Error: listen() on ipv4.", e);
	if (e->ipv6 >= 0 && listen(e->ipv6, MAX_CLIENT) == -1)
		sv_error("Error: listen() on ipv6.", e);
}
