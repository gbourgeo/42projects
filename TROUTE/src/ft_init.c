/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/29 02:29:04 by root              #+#    #+#             */
/*   Updated: 2016/09/26 17:24:20 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>

static void			ft_find_socket(void)
{
	int				on;
	socklen_t		sk;
	struct ip		*ip;

	e.sendsk = socket(e.af, SOCK_RAW, IPPROTO_RAW);
	if (e.sendsk < 0)
		ft_err("socket", NULL);
	sk = sizeof(e.source);
	if (getsockname(e.sendsk, (struct sockaddr *)&e.source, &sk) < 0)
		ft_err("getsockname", NULL);
	e.ident = ntohs(e.source.sin_port);
	ip = (struct ip *)e.outpack;
	ip->ip_v = IPVERSION;
	ip->ip_hl = 5;
	ip->ip_tos = 0;
	ip->ip_len = htons(e.datalen);
	ip->ip_id = htons(e.ident);
	ip->ip_off = 0;
	ip->ip_p = e.protocol;
	ip->ip_sum = 0;
	inet_pton(e.af, "0.0.0.0", &ip->ip_src);
//	ip->ip_src = (e.af == AF_INET) ? e.source.sin_addr : e.source6.sin6_addr;
	ip->ip_dst = e.dest.sin_addr;
	on = 1;
	if (setsockopt(e.sendsk, SOL_SOCKET, SO_SNDBUF, &e.datalen, sizeof(e.datalen)) < 0)
		ft_err("setsockopt SO_SNDBUF", NULL);
	if (setsockopt(e.sendsk, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on)) < 0)
		ft_err("setsockopt IP_HDRINCL", NULL);
	if (bind(e.sendsk, (struct sockaddr *)&e.source, sizeof(e.source)) < 0)
		ft_err("bind", NULL);
}

void				ft_init_icmp(void)
{
	if (e.packetlen < 0)
	{
		if (DEF_DATALEN >= 0)
			e.datalen = DEF_DATALEN;
	}
	else
	{
		if (e.packetlen >= e.headerlen)
			e.datalen = e.packetlen - e.headerlen;
	}
	e.num_probes = e.max_hops * e.nprobes;
	if (!(e.probes = calloc(e.num_probes, sizeof(t_probe))))
		ft_err("malloc", NULL);
	e.dest.sin_port = 0;
	if (e.datalen < (int)sizeof(struct icmphdr))
		e.datalen = sizeof(struct icmphdr);
	if (!(e.outpack = malloc(e.datalen)))
		ft_err("malloc", NULL);
	ft_bzero(e.outpack, e.datalen);
	e.protocol = IPPROTO_ICMP;
	ft_find_socket();
}

void				ft_init_udp(void)
{
	e.headerlen += sizeof(struct udphdr);
	if (e.packetlen < 0)
	{
		if (DEF_DATALEN >= sizeof(struct udphdr))
			e.datalen = DEF_DATALEN - sizeof(struct udphdr);
	}
	else
	{
		if (e.packetlen >= e.headerlen)
			e.datalen = e.packetlen - e.headerlen;
	}
	e.num_probes = e.max_hops * e.nprobes;
	if ((e.probes = calloc(e.num_probes, sizeof(t_probe))) == NULL)
		ft_err("malloc", NULL);
	if (!e.port)
		e.port = (e.module == DEFAULT) ? DEF_START_PORT : DEF_UDP_PORT;
	e.dest.sin_port = (e.module == DEFAULT) ? htons(e.port) : htons((u_int16_t)e.port);
	if (!(e.outpack = malloc(e.datalen)))
		ft_err("malloc", NULL);
	ft_bzero(e.outpack, e.datalen);
	e.protocol = IPPROTO_UDP;
	ft_find_socket();
}
