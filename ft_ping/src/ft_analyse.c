/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 21:37:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/29 01:06:39 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include "ft_err.h"
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netdb.h>

static int			ft_print_err(struct sockaddr_in *from, struct icmp *icp)
{
	struct ip		*oip;
	struct icmp		*oicmp;
	static char		*errlist[][50] = { ERRLIST_FULL };
	char			ip[255];

	oip = &icp->icmp_ip;
	oicmp = (struct icmp *)(oip + 1);
	if ((e.options[opt_v] && getuid() == 0) ||
		((oip->ip_dst.s_addr == e.source.sin_addr.s_addr) &&
			(oip->ip_p == IPPROTO_ICMP) && (oicmp->icmp_type == ICMP_ECHO) &&
			(oicmp->icmp_id == e.ident)))
	{
		getnameinfo((struct sockaddr *)from, sizeof(*from), ip, sizeof(ip),
					NULL, 0, NI_NAMEREQD | NI_DGRAM);
		if (*ip)
			printf("From %s %s icmp_seq=%d ", ip,
				   inet_ntoa(*(struct in_addr *)&from->sin_addr.s_addr),
				   ntohs(oicmp->icmp_seq));
		else
			printf("From %s icmp_seq=%d ",
				   inet_ntoa(*(struct in_addr *)&from->sin_addr.s_addr),
				   ntohs(oicmp->icmp_seq));
		if (icp->icmp_type > NR_ICMP_TYPES)
			return (printf("Bad ICMP type: %d\n", icp->icmp_type));
		if (icp->icmp_type == ICMP_DEST_UNREACH &&
			icp->icmp_code > NR_ICMP_UNREACH)
			return (printf("Dest Unreachable, Bad code: %d\n", icp->icmp_code));
		if (icp->icmp_type == ICMP_REDIRECT && icp->icmp_code > 3)
			return (printf("Redirect, Bad code: %d\n", icp->icmp_code));
		if (icp->icmp_type == ICMP_TIME_EXCEEDED && icp->icmp_code > 1)
			return (printf("Time exceeded, Bad code: %d\n", icp->icmp_code));
		printf("%s\n", errlist[icp->icmp_type][icp->icmp_code]);
		e.nerrors++;
		return (0);
	}
	return (1);
}

static void			ft_check_data(struct icmp *icp, int cc)
{
	u_char			*cp;
	u_char			*dp;
	int				i;

	cp = (u_char *)&icp->icmp_data[0];
	dp = &e.outpack[ICMP_MINLEN];
	cc -= ICMP_MINLEN;
	i = sizeof(struct timeval);
	cp += sizeof(struct timeval);
	dp += sizeof(struct timeval);
	cc -= sizeof(struct timeval);
	while (i < e.datalen && cc > 0)
	{
		if (*cp != *dp)
		{
			printf("\nwrong data byte #%d should be 0x%x but was 0x%x",
					i, *dp, *cp);
			printf("\ncp:");
			cp = (u_char *)&icp->icmp_data[0];
			i = 0;
			while (i < e.datalen)
			{
				if ((i % 16) == 8)
					printf("\n\t");
				printf("%2x ", *cp);
				i++;
				cp++;
			}
			printf("\ndp:");
			cp = &e.outpack[ICMP_MINLEN];
			i = 0;
			while (i < e.datalen)
			{
				if ((i % 16) == 8)
					printf("\n\t");
				printf("%2x ", *cp);
				i++;
				cp++;
			}
			break ;
		}
		i++;
		cp++;
		dp++;
		cc--;
	}
}

static void			print_data(int cc, struct icmp *icp, struct ip *ip, double triptime)
{
	if (e.options[opt_n])
		printf("%d bytes from %s: icmp_seq=%u", cc,
				e.srcip,
				ntohs(icp->icmp_seq));
	else
		printf("%d bytes from %s (%s): icmp_seq=%u", cc,
			   e.srcname,
			   e.srcip,
			   ntohs(icp->icmp_seq));
	printf(" ttl=%d", ip->ip_ttl);
	if (triptime >= 100)
		printf(" time=%f ms\n", triptime);
	else if (triptime >= 10)
		printf(" time=%.1f ms\n", triptime);
	else if (triptime >= 1)
		printf(" time=%.2f ms\n", triptime);
	else
		printf(" time=%.3f ms\n", triptime);
	ft_check_data(icp, cc);
	fflush(stdout);
}

void				ft_analyse(char *buf, int cc, struct sockaddr_in *from)
{
	struct ip		*ip;
	int				hlen;
	struct icmp		*icp;
	double			triptime;
	struct timeval	tv;

	ip = (struct ip *)buf;
	hlen = ip->ip_hl << 2;
	if (cc < hlen + ICMP_MINLEN)
	{
		if (e.options[opt_v])
			fprintf(stderr, "packet too short (%d bytes) from %s",
					cc,
					inet_ntoa(from->sin_addr));
		return ;
	}
	cc -= hlen;
	icp = (struct icmp *)(buf + hlen);
	if (icp->icmp_type == ICMP_ECHOREPLY)
	{
		if (icp->icmp_id != e.ident)
			return ;
		e.nreceived++;
		ft_memcpy(&tv, &icp->icmp_ip, sizeof(struct timeval));
		if ((e.end_time.tv_usec -= tv.tv_usec) < 0)
		{
			--e.end_time.tv_sec;
			e.end_time.tv_usec += 1000000;
		}
		e.end_time.tv_sec -= tv.tv_sec;
		if (!ft_strcmp(e.srcip, "127.0.0.1"))
		{
			triptime = ((double)e.end_time.tv_sec) * 10000.0 +
				((double)e.end_time.tv_usec) / 10000.0;
		}
		else
		{
			triptime = ((double)e.end_time.tv_sec) * 1000.0 +
				((double)e.end_time.tv_usec) / 1000.0;
		}
		if (triptime < e.tmin)
			e.tmin = triptime;
		if (triptime > e.tmax)
			e.tmax = triptime;
		if (!e.options[opt_q])
			print_data(cc, icp, ip, triptime);
	}
	else if (ft_print_err(from, icp) != 0)
		return ;
}
