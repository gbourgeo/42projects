/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_reply.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/19 01:13:01 by root              #+#    #+#             */
/*   Updated: 2016/09/19 02:15:10 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <netinet/ip_icmp.h>
#include <netinet/icmp6.h>

static void			ft_reply_err(int type, int code, int ret, t_probe *pb)
{
	if (!ret)
		return ;
	if (type == ICMP_TIME_EXCEEDED)
	{
		if (code == ICMP_EXC_TTL)
			return ;
	}
	else if (type == ICMP_DEST_UNREACH)
	{
		if (code == ICMP_UNREACH_NET ||
			code == ICMP_UNREACH_NET_UNKNOWN ||
			code == ICMP_UNREACH_ISOLATED ||
			code == ICMP_UNREACH_TOSNET)
			ft_strcpy(pb->err_str, "!N");
		else if (code == ICMP_UNREACH_HOST ||
				 code == ICMP_UNREACH_HOST_UNKNOWN ||
				 code == ICMP_UNREACH_TOSHOST)
			ft_strcpy(pb->err_str, "!H");
		else if (code == ICMP_UNREACH_NET_PROHIB ||
				 code == ICMP_UNREACH_HOST_PROHIB ||
				 code == ICMP_UNREACH_FILTER_PROHIB)
			ft_strcpy(pb->err_str, "!X");
		else if (code == ICMP_UNREACH_PORT)
		{
			ft_strcpy(pb->err_str, "");
			e.done = 1;
		}
		else if (code == ICMP_UNREACH_PROTOCOL)
			ft_strcpy(pb->err_str, "!P");
		else if (code == ICMP_UNREACH_NEEDFRAG)
			ft_strcpy(pb->err_str, "!F");
		else if (code == ICMP_UNREACH_SRCFAIL)
			ft_strcpy(pb->err_str, "!S");
		else if (code == ICMP_UNREACH_HOST_PRECEDENCE)
			ft_strcpy(pb->err_str, "!V");
		else if (code == ICMP_UNREACH_PRECEDENCE_CUTOFF)
			ft_strcpy(pb->err_str, "!C");
		else
			ft_strcpy(pb->err_str, "!");
	}
	pb->final = 1;
}

void				ft_parse_reply(t_probe *pb, int ret)
{
	struct ip		*ip;
	struct icmp		*icp;
	struct udphdr	*udp;
	int				hlen;
	u_char			type;
	u_char			code;

	ip = (struct ip *)e.inpack;
	hlen = ip->ip_hl << 2;
	icp = (struct icmp *)(e.inpack + hlen);
	type = icp->icmp_type;
	code = icp->icmp_code;
	if ((type == ICMP_TIMXCEED && code == ICMP_TIMXCEED_INTRANS) ||
		type == ICMP_UNREACH ||
		type == ICMP_ECHOREPLY)
	{
		ip = &icp->icmp_ip;
		hlen = ip->ip_hl << 2;
		udp = (struct udphdr *)((u_char *)ip + hlen);
		if (hlen + 12 <= ret - (((struct ip *)e.inpack)->ip_hl << 2)
			&& ip->ip_p == IPPROTO_UDP
			&& udp->source == htons(e.ident)
			&& udp->dest == htons(pb->seq))
			ft_reply_err(type, code, ret, pb);
//			return ((type == ICMP_TIMXCEED ) ? -1 : code + 1);
	}
}
