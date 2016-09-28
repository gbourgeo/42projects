/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_reply.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 01:13:01 by root              #+#    #+#             */
/*   Updated: 2016/09/27 14:36:38 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <netinet/ip_icmp.h>
#include <stdio.h>

void				ft_reply_err(t_probe *pb, int type, int code, int info)
{
	char			*str;

	str = NULL;
	if (type == ICMP_TIMXCEED)
		return ;
	code--;
	if (code == ICMP_UNREACH_PORT)
	{
		if (((struct ip *)e.inpack)->ip_ttl <= 1)
			str = " !";
	}
	else if (code == ICMP_UNREACH_NET)
		str = " !N";
	else if (code == ICMP_UNREACH_HOST)
		str = " !H";
	else if (code == ICMP_UNREACH_PROTOCOL)
		str = " !P";
	else if (code == ICMP_UNREACH_NEEDFRAG)
	{
		snprintf(pb->err_str, sizeof(pb->err_str), " !F-%d", info);
		str = pb->err_str;
	}
	else if (code == ICMP_UNREACH_SRCFAIL)
		str = " !S";
	else if (code == ICMP_UNREACH_FILTER_PROHIB)
		str = " !X";
	else if (code == ICMP_UNREACH_HOST_PRECEDENCE)
		str = " !V";
	else if (code == ICMP_UNREACH_PRECEDENCE_CUTOFF)
		str = " !C";
	else
	{
		snprintf(pb->err_str, sizeof(pb->err_str), " !<%d>", code);
		str = pb->err_str;
	}

	if (str)
		ft_strncpy(pb->err_str, str, sizeof(pb->err_str));
	pb->final = 1;
}

static int			ft_parse_icmp(u_char* data, t_probe *pb)
{
	struct icmp		*icmp;

	icmp = (struct icmp *)data;
	return (icmp->icmp_id == htons(e.ident) && icmp->icmp_seq == htons(pb->seq));
}

static int			ft_parse_udp(u_char *data, t_probe *pb)
{
	struct udphdr	*udp;

	udp = (struct udphdr *)data;
	return (ntohs(udp->source) == e.ident && ntohs(udp->dest) == pb->seq);
}

void				ft_parse(t_probe *pb, int cc)
{
	static int		(*ft_check[])(u_char *, t_probe *) = { ft_parse_udp,
														   ft_parse_udp,
														   ft_parse_icmp };
	struct ip		*ip;
	struct icmp		*icp;
	u_char			type;
	u_char			code;
	u_char			info;
	int				hlen;

	ip = (struct ip *)e.inpack;
	hlen = ip->ip_hl << 2;
	if (cc < hlen + ICMP_MINLEN)
		return ;
	cc -= hlen;
	icp = (struct icmp *)(e.inpack + hlen);
	type = icp->icmp_type;
	code = icp->icmp_code;
	info = (code != ICMP_UNREACH_NEEDFRAG) ? 0 : ntohs(icp->icmp_nextmtu);

	/* printf("0: %d:%d, %d-%d %d-%d _ ", type, ICMP_ECHOREPLY, */
	/* 		   ((struct icmp *)icp)->icmp_id, htons(e.ident), */
	/* 		   ((struct icmp *)icp)->icmp_seq, htons(pb->seq)); */

	if (type == ICMP_ECHOREPLY &&
		e.protocol == IPPROTO_ICMP &&
		ft_check[e.module]((u_char *)icp, pb))
	{
		pb->final = 1;
		return ;
	}

	/* printf("1: %d %d %d, %d %d, %d %d\n", */
	/* 	   type, ICMP_TIMXCEED, ICMP_UNREACH, */
	/* 	   code, ICMP_TIMXCEED_INTRANS, */
	/* 	   ip->ip_ttl, pb->seq); */

	if ((type == ICMP_TIMXCEED && code == ICMP_TIMXCEED_INTRANS) ||
		type == ICMP_UNREACH)
	{
		struct ip	*hip;
		u_char		*inner;

		hip = &icp->icmp_ip;
		hlen = hip->ip_hl << 2;
		inner = (u_char *)((u_char *)hip + hlen);

		/* printf("2: %d <= %d, ", hlen + 12, cc); */
		/* printf("%d %d, %d %d, %d %d\n", */
		/* 	   ((struct icmp *)inner)->icmp_id, htons(e.ident), */
		/* 	   ((struct icmp *)inner)->icmp_cksum, 0xffff, */
		/* 	   ((struct icmp *)inner)->icmp_seq, htons(pb->seq)); */

		if (hlen + 12 <= cc &&
			hip->ip_p == e.protocol &&
			ft_check[e.module](inner, pb))
		{
			hlen = (type == ICMP_TIMXCEED) ? -1 : code + 1;
			ft_reply_err(pb, type, hlen, info);
		}
	}
	if (!ft_memcmp(&e.from.sin_addr, &e.dest.sin_addr, sizeof(e.from.sin_addr)))
		pb->final = 1;
}
