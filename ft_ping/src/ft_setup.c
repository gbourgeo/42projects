/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/09 14:16:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/08/24 16:50:13 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include <sys/time.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <stdio.h>
#include <errno.h>
#include <arpa/inet.h>

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

void					ft_pinger(void)
{
	u_char				*pack;
	struct icmp			*icp;
	int					offset;
	struct ip			*ip;
	int					i;

	pack = e.outpack;
	icp = (struct icmp *)e.outpack;
	icp->icmp_type = ICMP_ECHO;
	icp->icmp_code = 0;
	icp->icmp_cksum = 0;
	icp->icmp_seq = htons(++e.ntransmitted);
	icp->icmp_id = e.ident;
	gettimeofday(&e.start_time, NULL);
	ft_memcpy(&pack[ICMP_MINLEN], &e.start_time, sizeof(struct timeval));
	offset = ICMP_MINLEN + e.datalen;
	icp->icmp_cksum = ft_cksum((u_short *)icp, offset);
	offset += sizeof(struct ip);
	ip = (struct ip *)e.outpackhdr;
	ip->ip_v = IPVERSION;
	ip->ip_hl = sizeof(struct ip) >> 2;
	ip->ip_tos = 0;
	ip->ip_id = 0;
	ip->ip_off = 0;
	ip->ip_ttl = 64;
	ip->ip_p = IPPROTO_ICMP;
	ip->ip_src.s_addr = INADDR_ANY;
	ip->ip_dst = e.source.sin_addr;
	ip->ip_len = htons(offset);
	ip->ip_sum = ft_cksum((u_short *)e.outpackhdr, offset);
	pack = e.outpackhdr;
	i = sendto(e.sock, (char *)pack, offset, 0,
				(struct sockaddr *)&e.source, sizeof(e.source));
	if (i < 0 || i != offset)
	{
		if (i < 0)
		{
			fprintf(stderr, "%s: sendto \n", e.prog);
			perror("");
		}
		else
			fprintf(stderr, "%s: partial write: %d of %d bytes\n", e.prog, i, offset);
	}
}

void					ft_setup(void)
{
	struct msghdr		msg;
	struct iovec		iov;
	struct sockaddr_in	from;
	struct cmsghdr		*cmsg;
	int					i;

	gettimeofday(&e.start, NULL);
	ft_alarm(0);
	while (1)
	{
		ft_memset(&e.inpack, 0, sizeof(e.inpack));
		ft_memset(&from, 0, sizeof(from));
		ft_memset(&e.ctrl, 0, sizeof(e.ctrl));
		ft_memset(&msg, 0, sizeof(msg));
		msg.msg_name = &from;
		msg.msg_control = (caddr_t)e.ctrl;
		msg.msg_iov = &iov;
		msg.msg_iovlen = 1;
		iov.iov_base = e.inpack;
		iov.iov_len = IP_MAXPACKET;
		msg.msg_controllen = sizeof(e.ctrl);
		msg.msg_namelen = sizeof(from);
		cmsg = (struct cmsghdr *)e.ctrl;
		i = recvmsg(e.sock, &msg, 0);
		if (i < 0)
		{
			if (errno == EINTR)
				continue ;
			fprintf(stderr, "%s: recvmsg: ", e.prog);
			perror("");
			continue ;
		}
		if (cmsg->cmsg_level == SOL_SOCKET &&
			cmsg->cmsg_type == SCM_TIMESTAMP &&
			cmsg->cmsg_len == CMSG_LEN(sizeof(struct timeval)))
			ft_memcpy(&e.end_time, CMSG_DATA(cmsg), sizeof(struct timeval));
		else
			gettimeofday(&e.end_time, NULL);
		ft_analyse((char *)e.inpack, i, &from);
	}
	ft_finish(0);
}
