/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/12 14:48:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/09 09:51:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static int				ft_findsocket(struct addrinfo *p, int ip)
{
	int					sock;

	sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
	if (sock == -1)
	{
		ft_putendl_fd("Can't open IP V6 socket", 2);
		return (-1);
	}
	if (!ip || !setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY, &ip, sizeof(ip)))
	{
		if (bind(sock, p->ai_addr, p->ai_addrlen) != -1)
		{
			ft_aff_ip(p, ip);
			ft_putchar('\n');
			return (sock);
		}
		if (ip == v4)
			ft_putendl_fd("Can't bind IPV4 socket", 2);
		else
			ft_putendl_fd("Can't bind IPV6 socket", 2);
	}
	else
		ft_putendl_fd("Can't set socket option IPV6_ONLY", 2);
	close(sock);
	return (-1);
}

static void				init_addrinfo(char *port, struct addrinfo **results)
{
	struct addrinfo		hints;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_protocol = IPPROTO_TCP;
	if (getaddrinfo(NULL, port, &hints, results))
		ft_error("ERROR: getaddrinfo() returns.");
}

static void				ft_getaddrinfo(char *port, t_envi *e)
{
	struct addrinfo		*results;
	struct addrinfo		*p;
	int					on;

	init_addrinfo(port, &results);
	p = results;
	on = 1;
	e->ip[v4] = -1;
	e->ip[v6] = -1;
	while (p != NULL && (e->ip[v4] < 0 || e->ip[v6] < 0))
	{
		if (e->ip[v4] < 0 && p->ai_family == AF_INET)
			e->ip[v4] = ft_findsocket(p, v4);
		if (e->ip[v6] < 0 && p->ai_family == AF_INET6)
			e->ip[v6] = ft_findsocket(p, v6);
		if (e->ip[v4] < 0 || e->ip[v6] < 0)
			p = p->ai_next;
	}
	if (p == NULL)
		ft_error("Error: No IPv4 or IPv6 server found.");
	if (setsockopt(e->ip[v4], SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
		ft_error("Error: setsockopt(sock(AF_INET, SO_REUSEADDR) failed");
	if (setsockopt(e->ip[v6], SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
		ft_error("Error: setsockopt(sock(AF_INET6, SO_REUSEADDR) failed");
	freeaddrinfo(results);
}

static void				init_server(char *port, t_envi *e)
{
	ft_getaddrinfo(port, e);
	if (listen(e->ip[v4], CLIENTS_MAX) == -1)
		ft_error("ERROR: listen(sock[0]: AF_INET).");
	if (listen(e->ip[v6], CLIENTS_MAX) == -1)
		ft_error("ERROR: listen(sock[1]: AF_INET6).");
	e->home = getcwd(NULL, 0);
	e->pwd = ft_strdup("");
	e->oldpwd = ft_strdup("");
	if (!e->home || !e->pwd || !e->oldpwd)
		ft_error("ERROR: init_server() failed.");
}

int						main(int ac, char **av)
{
	t_envi				sv;

	if (ac < 2 || ac > 3)
		return (usage(av[0], SERVER));
	if (av[2] && ft_strcmp(av[2], "-i") != 0)
		return (usage(av[0], SERVER));
	ft_memset(&sv, 0, sizeof(t_envi));
	init_server(av[1], &sv);
	if (av[2] && !ft_strcmp(av[2], "-i"))
		sv.success = 1;
	sv_loop(&sv);
	return (0);
}
