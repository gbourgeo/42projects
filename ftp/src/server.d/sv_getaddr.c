/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_getaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 01:48:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/25 23:59:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# define _XOPEN_SOURCE 700
#endif
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "sv_main.h"

static void		sv_aff_ip(struct addrinfo *p, int version)
{
	struct sockaddr_in	*ipv4;
	struct sockaddr_in6	*ipv6;
	void				*addr;
	char				name[INET6_ADDRSTRLEN];

	if (version == v6)
	{
		ipv6 = (struct sockaddr_in6 *)p->ai_addr;
		addr = &(ipv6->sin6_addr);
		ft_putstr("\033[4mIPv6\033[0m: \x1B[3m");
	}
	else
	{
		ipv4 = (struct sockaddr_in *)p->ai_addr;
		addr = &(ipv4->sin_addr);
		ft_putstr("\033[4mIPv4\033[0m: \x1B[3m");
	}
	inet_ntop(p->ai_family, addr, name, sizeof(name));
	ft_putstr(name);
	ft_putendl("\t\x1B[0;32mONLINE\033[0m");
}

static int		sv_findsocket(struct addrinfo *p, int ip, t_server *sv)
{
	int			sock;
	int			on;

	if (sv->ip[ip] >= 0)
		return (sv->ip[ip]);
	on = 1;
	sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
	if (sock == -1)
		return (-1);
	if (ip == v4
	|| !setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY, &ip, sizeof(ip)))
		if (!setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)))
			if (!bind(sock, p->ai_addr, p->ai_addrlen))
			{
				if (sv->interactive)
					sv_aff_ip(p, ip);
				return (sock);
			}
	close(sock);
	return (-1);
}

static int		init_addrinfo(struct addrinfo **results, t_server *sv)
{
	struct addrinfo	hints;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_protocol = IPPROTO_TCP;
	if (getaddrinfo(NULL, sv->port, &hints, results))
		return (ERR_GETADDR);
	sv->ip[v4] = -SV_VERSION(sv->version, v4);
	sv->ip[v6] = -SV_VERSION(sv->version, v6);
	return (IS_OK);
}

int				sv_getaddrinfo(t_server *sv)
{
	struct addrinfo	*results;
	struct addrinfo	*p;
	int				errnb;

	if ((errnb = init_addrinfo(&results, sv)) != IS_OK)
		return (errnb);
	p = results;
	while (p && (sv->ip[v4] < 0 || sv->ip[v6] < 0))
	{
		if (SV_VERSION(sv->version, v4) && p->ai_family == AF_INET)
			sv->ip[v4] = sv_findsocket(p, v4, sv);
		if (SV_VERSION(sv->version, v6) && p->ai_family == AF_INET6)
			sv->ip[v6] = sv_findsocket(p, v6, sv);
		p = p->ai_next;
	}
	freeaddrinfo(results);
	if (SV_VERSION(sv->version, v4) && sv->ip[v4] < 0)
		return (ERR_NO_IPV4_AVAIL);
	if (SV_VERSION(sv->version, v6) && sv->ip[v6] < 0)
		return (ERR_NO_IPV6_AVAIL);
	if (SV_VERSION(sv->version, v4) && listen(sv->ip[v4], CLIENTS_MAX) == -1)
		return (ERR_LISTEN_V4);
	if (SV_VERSION(sv->version, v6) && listen(sv->ip[v6], CLIENTS_MAX) == -1)
		return (ERR_LISTEN_V6);
	return (IS_OK);
}
