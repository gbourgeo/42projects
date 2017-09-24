/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pinger.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 21:23:36 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/29 00:04:18 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include <sys/time.h>
#include <stdio.h>

static int				ft_cksum(u_short *addr, int len)
{
	int					nleft;
	int					sum;
	u_short				*w;
	u_short				answer;

	nleft = len;
	sum = 0;
	w = addr;
	while (nleft > 1)
	{
		sum += *w++;
		nleft -= 2;
	}
	if (nleft == 1)
	{
		*(u_char *)(&answer) = *(u_char *)w;
		sum += answer;
	}
	sum = (sum >> 16) + (sum & 0xFFFF);
	sum += (sum >> 16);
	answer = ~sum;
	return (answer);
}

static void				ft_init_icmp(u_char *pack, int offset)
{
	struct icmp			*icp;

	icp = (struct icmp *)e.outpack;
	icp->icmp_type = ICMP_ECHO;
	icp->icmp_code = 0;
	icp->icmp_cksum = 0;
	icp->icmp_seq = htons(++e.ntransmitted);
	icp->icmp_id = e.ident;
	gettimeofday(&e.start_time, NULL);
	ft_memcpy(&pack[ICMP_MINLEN], &e.start_time, sizeof(struct timeval));
	icp->icmp_cksum = ft_cksum((u_short *)icp, offset);
}

static void				ft_init_ip(int offset)
{
	struct ip			*ip;

	ip = (struct ip *)e.outpackhdr;
	ip->ip_v = IPVERSION;
	ip->ip_hl = sizeof(struct ip) >> 2;
	ip->ip_tos = 0;
	ip->ip_id = 0;
	ip->ip_off = 0;
	ip->ip_ttl = e.ttl;
	ip->ip_p = IPPROTO_ICMP;
	ip->ip_src.s_addr = INADDR_ANY;
	ip->ip_dst = e.source.sin_addr;
	ip->ip_len = htons(offset);
	ip->ip_sum = ft_cksum((u_short *)e.outpackhdr, offset);
}

void					ft_pinger(void)
{
	u_char				*pack;
	int					offset;
	int					i;

	pack = e.outpack;
	offset = ICMP_MINLEN + e.datalen;
	ft_init_icmp(pack, offset);
	offset += sizeof(struct ip);
	ft_init_ip(offset);
	pack = e.outpackhdr;
	i = sendto(e.sock, (char *)pack, offset, 0,
				(struct sockaddr *)&e.source, sizeof(e.source));
	if (i < 0 || i != offset)
	{
		if (i < 0)
		{
			fprintf(stderr, "%s: sendto: ", e.prog);
			perror("");
			return ;
		}
		fprintf(stderr, "%s: partial write: %d of %d bytes", e.prog, i, offset);
		fprintf(stderr, "\n");
	}
}
