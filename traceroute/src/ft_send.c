/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_send.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/18 00:35:46 by root              #+#    #+#             */
/*   Updated: 2016/09/28 21:47:03 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <errno.h>
#include <netinet/ip_icmp.h>

struct ipovly {
	caddr_t			ih_next, ih_prev;/* for protocol sequence q's */
	u_char			ih_x1;/* (unused) */
	u_char			ih_pr;/* protocol */
	short			ih_len;/* protocol length */
	struct in_addr	ih_src;/* source internet address */
	struct in_addr	ih_dst;/* destination internet address */
};

static u_short			in_cksum(register u_short *addr, register int len)
{
	register int		nleft = len;
	register u_short	*w = addr;
	register u_short	answer;
	register int		sum = 0;

	while (nleft > 1)  {
		sum += *w++;
		nleft -= 2;
	}
	if (nleft == 1)
		sum += *(u_char *)w;
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = ~sum;
	return (answer);
}

static u_short			p_cksum(struct ip *ip, u_short *data, int len)
{
	struct ipovly		ipo;
	u_short				sumh, sumd;
	u_long				sumt;

	ipo.ih_pr = ip->ip_p;
	ipo.ih_len = htons(len);
	ipo.ih_src = ip->ip_src;
	ipo.ih_dst = ip->ip_dst;
	sumh = in_cksum((u_short*)&ipo, sizeof(ipo));
	sumd = in_cksum((u_short*)data, len);
	sumt = (sumh << 16) | (sumd);
	return ~in_cksum((u_short*)&sumt, sizeof(sumt));
}

static int				ft_do_send(int fd)
{
	int					i;

	i = sendto(fd, (char *)e.outpack, e.datalen, 0,
				(struct sockaddr *)&e.dest, sizeof(e.dest));
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

void					ft_send_icmp(t_probe *pb, int ttl)
{
	static int			seq = 0;
	int					fd;
	struct ip			*ip;
	struct icmp			*icmp;

	if (!seq)
		seq = (e.port) ? e.port : 1;
	fd = socket(e.af, SOCK_RAW, IPPROTO_ICMP);
	if (fd < 0)
		ft_err("socket", NULL);
	ip = (struct ip *)e.outpack;
	ip->ip_ttl = ttl;
	icmp = (struct icmp *)(ip + 1);
	icmp->icmp_type = ICMP_ECHO;
	icmp->icmp_id = htons(e.ident);
	icmp->icmp_seq = htons(seq);
	icmp->icmp_code = 0;
	icmp->icmp_cksum = 0;
	if ((icmp->icmp_cksum = in_cksum((u_short *)icmp, (e.datalen - sizeof(*ip)))) == 0)
		icmp->icmp_cksum = 0xffff;
	pb->send_time = ft_get_time();
	if (ft_do_send(e.sendsk) < 0)
	{
		close(fd);
		pb->send_time = 0;
		return ;
	}
	pb->fd = fd;
	pb->seq = seq++;
}

void					ft_send_udp(t_probe *pb, int ttl)
{
	int					fd;
	struct ip			*ip;
	struct udphdr		*udp;

	fd = socket(e.af, SOCK_RAW, IPPROTO_ICMP);
	if (fd < 0)
		ft_err("socket", NULL);
	ip = (struct ip *)e.outpack;
	ip->ip_ttl = ttl;
	udp = (struct udphdr *)(ip + 1);
	udp->source = htons(e.ident);
	udp->dest = htons(e.port);
	udp->len = htons((u_short)(e.datalen - sizeof(*ip)));
	udp->check = 0;
	if ((udp->check = p_cksum(ip, (u_short *)udp, e.datalen - sizeof(*ip))) == 0)
		udp->check = 0xffff;
	pb->send_time = ft_get_time();
	if (ft_do_send((e.local) ? e.sendsk : fd) < 0)
	{
		close(fd);
		pb->send_time = 0;
		return ;
	}
	pb->fd = fd;
	pb->seq = e.dest.sin_port;
	if (e.module == DEFAULT)
	{
		e.port++;
		e.dest.sin_port = htons(e.port);
	}
}
