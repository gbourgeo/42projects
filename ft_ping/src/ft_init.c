/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/08 01:35:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/29 02:54:18 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <limits.h>
#include <netinet/ip_icmp.h>

static void			ft_err(char *msg, char *err_msg)
{
	fprintf(stderr, "%s: %s %s\n", e.prog, msg, err_msg);
	exit(2);
}

static void			ft_setsockopt(void)
{
	socklen_t		on;
	int				ret;

	on = 1;
	ret = setsockopt(e.sock, SOL_SOCKET, SO_BROADCAST, (char *)&on, sizeof(on));
	if (ret < 0)
		ft_err("setsockopt", "(SO_BROADCAST)");
	if (setsockopt(e.sock, IPPROTO_IP, IP_HDRINCL, (char *)&on, sizeof(on)) < 0)
		ft_err("setsocket", "(IPHDRINCL)");
	on = 64;
	if (setsockopt(e.sock, IPPROTO_IP, IP_TTL, (char *)&on, sizeof(on)) < 0)
		ft_err("setsocket", "(IPHDRINCL)");
	on = IP_MAXPACKET + 128;
	setsockopt(e.sock, SOL_SOCKET, SO_RCVBUF, (char *)&on, sizeof(on));
	if (getuid() == 0)
		setsockopt(e.sock, SOL_SOCKET, SO_SNDBUF, (char *)&on, sizeof(on));
	e.start_time.tv_sec = 1;
	e.start_time.tv_usec = 0;
	ret = sizeof(struct timeval);
	setsockopt(e.sock, SOL_SOCKET, SO_SNDTIMEO, &e.start_time, ret);
}

static void			ft_getinfo(struct addrinfo *res)
{
	ft_memcpy(e.hostname, res->ai_canonname, sizeof(e.hostname));
	ft_memcpy(&e.source, res->ai_addr, sizeof(e.source));
	inet_ntop(res->ai_family, &e.source.sin_addr, e.srcip, sizeof(e.srcip));
	if (!ft_strcmp(e.hostname, e.srcip))
		e.options |= OPT_NUMERIC;
	freeaddrinfo(res);
}

static void			ft_socket(void)
{
	struct addrinfo	hints;
	struct addrinfo	*res;
	struct addrinfo	*tmp;
	int				i;

	ft_memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;
	hints.ai_flags = AI_CANONNAME;
	if ((i = getaddrinfo(e.hostname, NULL, &hints, &res)) != 0)
		ft_err("unknown host", e.hostname);
	tmp = res;
	while (tmp)
	{
		e.sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
		if (e.sock >= 0)
			break ;
		tmp = tmp->ai_next;
	}
	if (tmp == NULL)
		ft_err(e.prog, "socket");
	ft_getinfo(res);
}

void				ft_init(void)
{
	u_char			*data;
	int				i;

	e.tmin = LONG_MAX;
	data = &e.outpack[ICMP_MINLEN + sizeof(struct timeval)];
	i = sizeof(struct timeval);
	while (i < e.datalen)
		*data++ = i++;
	e.ident = htons(getpid() & 0xFFFF);
	ft_socket();
	ft_setsockopt();
	if (e.source.sin_family == AF_INET)
		printf("PING %s (%s) %d(%d) bytes of data.\n", e.hostname, e.srcip,
				e.datalen, e.datalen + 8 + 20);
	else
		printf("PING %s %d bytes of data.\n", e.hostname, e.datalen);
}
