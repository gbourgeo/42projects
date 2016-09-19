/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_send.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/18 00:35:46 by root              #+#    #+#             */
/*   Updated: 2016/09/19 02:26:51 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <errno.h>
#include <netinet/ip_icmp.h>
#include <netinet/icmp6.h>

static int				ft_cksum(uint16_t *p, u_int len)
{
	size_t				nw;
	unsigned int		sum;
	uint16_t			res;

	nw = len / 2;
	sum = 0;
	while (nw--)
		sum += *p++;
	if (len & 0x1)
		sum += htons(*((unsigned char *)p) << 8);
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	res = ~sum;
	if (!res)
		res = ~0;
	return (res);
}

static int				ft_do_send(int fd, t_addr_any *addr)
{
	int					i;

	i = sendto(fd, (char *)e.outpack, e.datalen, 0,
			   (struct sockaddr *)&addr->sin, sizeof(*addr));
	if (i < 0)
	{
		if (errno == ENOBUFS || errno == EAGAIN)
			return (i);
		if (errno == EMSGSIZE)
			return (0);
		ft_err("sendto", NULL);
	}
	return (i);
}

void					ft_send_udp(t_probe *pb, int ttl)
{
	int					fd;
	struct icmp			*icp;

	fd = socket(e.af, SOCK_DGRAM, e.protocol);
	if (fd < 0)
		ft_err("socket", NULL);
	ft_tune_socket(fd);
	ft_set_ttl(fd, ttl);
	if (connect(fd, &e.source.sa, sizeof(e.source)) < 0)
		ft_err("connect", NULL);
	ft_recverr(fd);
	icp = (struct icmp *)e.outpack;
	icp->icmp_type = ICMP_ECHO;
	icp->icmp_id = htons(e.ident);
	icp->icmp_seq = htons(pb - e.probes + 1);
	icp->icmp_cksum = 0;
	icp->icmp_cksum = ft_cksum((uint16_t *)icp, e.datalen);
	pb->send_time = ft_get_time();
	if (ft_do_send(fd, &e.source) < 0)
	{
		close(fd);
		pb->send_time = 0;
		return ;
	}
	pb->fd = fd;
	pb->seq = e.source.sin.sin_port;
	if (e.module == DEFAULT)
	{
		e.port++;
		e.source.sin.sin_port = htons(e.port);
	}
}

void					ft_send_icmp(t_probe *pb, int ttl)
{
	static int			last_ttl = 0;
	static int			seq = 0;
	struct icmp			*icmp;
	struct icmp6_hdr	*icmp6;

	if (!seq)
		seq = (e.port) ? e.port : 1;
	if (ttl != last_ttl)
	{
		ft_set_ttl(e.sendsk, ttl);
		last_ttl = ttl;
	}
	if (e.af == AF_INET)
	{
		icmp = (struct icmp *)e.outpack;
		icmp->icmp_type = ICMP_ECHO;
		icmp->icmp_code = 0;
		icmp->icmp_cksum = 0;
		icmp->icmp_id = htons(e.ident);
		icmp->icmp_seq = htons(seq);
		icmp->icmp_cksum = ft_cksum((uint16_t *)e.outpack, e.datalen);
	}
	else
	{
		icmp6 = (struct icmp6_hdr *)e.outpack;
		icmp6->icmp6_type = ICMP6_ECHO_REQUEST;
		icmp6->icmp6_code = 0;
		icmp6->icmp6_cksum = 0;
		icmp6->icmp6_id = htons(e.ident);
		icmp6->icmp6_seq = htons(seq);
	}
	pb->send_time = ft_get_time();
	if (ft_do_send(e.sendsk, &e.source) < 0)
	{
		pb->send_time = 0;
		return ;
	}
	pb->fd = e.sendsk;
	pb->seq = seq++;
}
