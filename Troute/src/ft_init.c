/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/29 02:29:04 by root              #+#    #+#             */
/*   Updated: 2016/09/19 02:32:15 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <netinet/ip_icmp.h>

void				ft_init_icmp(void)
{
	t_addr_any		addr;
	int				raw;
	int				dgram;
	int				sk;

	raw = 0;
	dgram = 0;
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
	e.probes = calloc(e.num_probes, sizeof(t_probe));
	if (!e.probes)
		ft_err("malloc", NULL);

	e.source.sin.sin_port = 0;
	if (e.datalen < (int)sizeof(struct icmphdr))
		e.datalen = sizeof(struct icmphdr);
	e.outpack = malloc(e.datalen);
	if (!e.outpack)
		ft_err("malloc", NULL);
	ft_bzero(e.outpack, e.datalen);
	e.protocol = (e.af == AF_INET) ? IPPROTO_ICMP : IPPROTO_ICMPV6;
	if (!raw)
	{
		e.sendsk = socket(e.af, SOCK_DGRAM, e.protocol);
		if (e.sendsk < 0 && dgram)
			ft_err("socket", NULL);
	}
	if (!dgram)
	{
		sk = socket(e.af, SOCK_RAW, e.protocol);
		if (sk < 0)
		{
			if (raw || e.sendsk < 0)
				ft_err("socket", NULL);
			dgram = 1;
		}
		else
		{
			if (e.sendsk > 0)
				close(e.sendsk);
			e.sendsk = sk;
		}
	}
	ft_tune_socket(e.sendsk);
	if (connect(e.sendsk, &e.source.sa, sizeof(e.source)) < 0)
		ft_err("connect", NULL);
	ft_recverr(e.sendsk);
	if (dgram)
	{
		sk = sizeof(addr);
		if (getsockname(e.sendsk, &addr.sa, (socklen_t *)&sk) < 0)
			ft_err("getsockname", NULL);
		e.ident = ntohs(addr.sin.sin_port);
	}
	else
		e.ident = getpid() & 0xffff;
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
	if ((e.probes = (t_probe *)calloc(e.num_probes, sizeof(t_probe))) == NULL)
		ft_err("malloc", NULL);

	if (!e.port)
		e.port = DEF_UDP_PORT;
	e.source.sin.sin_port = htons((u_int16_t)e.port);
	e.outpack = malloc(e.datalen);
	if (!e.outpack)
		ft_err("malloc", NULL);
	ft_bzero(e.outpack, e.datalen);
	e.protocol = IPPROTO_UDP;
	e.ident = getpid();
}

void				ft_init_default(void)
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
	if ((e.probes = (t_probe *)calloc(e.num_probes, sizeof(t_probe))) == NULL)
		ft_err("malloc", NULL);

	if (!e.port)
		e.port = DEF_START_PORT;
	e.source.sin.sin_port = htons(e.port);
	e.outpack = malloc(e.datalen);
	if (!e.outpack)
		ft_err("malloc", NULL);
	ft_bzero(e.outpack, e.datalen);
	e.protocol = IPPROTO_UDP;
	e.ident = getpid();
}
