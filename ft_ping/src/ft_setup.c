/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/09 14:16:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/08/11 00:03:35 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include <sys/time.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>

void				ft_setup(void)
{
	struct timeval	tv;
	struct icmphdr	*icp;

	tv.tv_sec = 1;
	tv.tv_usec = 0;
	setsockopt(e.sock, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
	setsockopt(e.sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
	gettimeofday(&e.start_time, NULL);	
	while (1)
	{
		icp = (struct icmphdr *)e.outpack;
		icp->type = ICMP_ECHO;
		icp->code = 0;
//		icp->checksum = ft_cksum(icp, datalen + 8, 0);
		icp->un.echo.sequence = htons(e.ntransmitted + 1);
		icp->un.echo.id = htons(getpid() & 0xFFFF);
	}
}
