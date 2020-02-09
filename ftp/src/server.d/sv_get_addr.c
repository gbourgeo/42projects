/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_get_addr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 01:48:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/08 18:48:41 by gbourgeo         ###   ########.fr       */
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
#include <ifaddrs.h>
#ifdef __linux__
# include <linux/if.h>
#else
# include <net/if.h>
#endif
#include "sv_main.h"

static int		sv_getipaddress(int sock, int version, t_server *sv)
{
	struct ifaddrs	*interface;
	struct ifaddrs	*tmp;

	if (getifaddrs(&interface) == 0)
	{
		tmp = interface;
		while (tmp != NULL)
			if (tmp->ifa_addr && !(tmp->ifa_flags & IFF_LOOPBACK)
			&& ((version == sv_v4 && tmp->ifa_addr->sa_family == AF_INET)
			|| (version == sv_v6 && tmp->ifa_addr->sa_family == AF_INET6)))
			{
				if (getnameinfo(tmp->ifa_addr, (version == sv_v4)
				? sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6),
				sv->addr[version], sizeof(sv->addr[version]), NULL, 0,
				NI_NUMERICHOST) != 0)
					break ;
				freeifaddrs(interface);
				return (sock);
			}
			else
				tmp = tmp->ifa_next;
	}
	freeifaddrs(interface);
	close(sock);
	return (-1);
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
	if (ip == sv_v4
	|| !setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY, &ip, sizeof(ip)))
		if (!setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)))
			if (!bind(sock, p->ai_addr, p->ai_addrlen))
				return (sv_getipaddress(sock, ip, sv));
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
	sv->ip[sv_v4] = -FT_CHECK(sv->options, sv_v4);
	sv->ip[sv_v6] = -FT_CHECK(sv->options, sv_v6);
	return (IS_OK);
}

int				sv_get_addrinfo(t_server *sv)
{
	struct addrinfo	*results;
	struct addrinfo	*p;
	int				errnb;

	if ((errnb = init_addrinfo(&results, sv)) != IS_OK)
		return (errnb);
	p = results;
	while (p && (sv->ip[sv_v4] < 0 || sv->ip[sv_v6] < 0))
	{
		if (FT_CHECK(sv->options, sv_v4) && p->ai_family == AF_INET)
			sv->ip[sv_v4] = sv_findsocket(p, sv_v4, sv);
		if (FT_CHECK(sv->options, sv_v6) && p->ai_family == AF_INET6)
			sv->ip[sv_v6] = sv_findsocket(p, sv_v6, sv);
		p = p->ai_next;
	}
	freeaddrinfo(results);
	if (FT_CHECK(sv->options, sv_v4) && sv->ip[sv_v4] < 0)
		return (ERR_NO_IPV4_AVAIL);
	if (FT_CHECK(sv->options, sv_v6) && sv->ip[sv_v6] < 0)
		return (ERR_NO_IPV6_AVAIL);
	if (FT_CHECK(sv->options, sv_v4) && listen(sv->ip[sv_v4], CLIENTS_MAX) < 0)
		return (ERR_LISTEN_V4);
	if (FT_CHECK(sv->options, sv_v6) && listen(sv->ip[sv_v6], CLIENTS_MAX) < 0)
		return (ERR_LISTEN_V6);
	return (IS_OK);
}
