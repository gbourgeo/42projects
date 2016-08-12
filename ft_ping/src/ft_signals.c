/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/09 14:23:13 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/08/09 14:29:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include <signal.h>
#include <stdio.h>

static void		ft_finish(int sig)
{
	(void)sig;
	signal(SIGINT, SIG_IGN);
	printf("\n--- %s ping statistics ---\n", e.hostname);
	printf("%ld packets transmitted, ", e.ntransmitted);
	printf("%ld packets received, ", e.nreceived);
	if (e.ntransmitted)
	{
		if (e.nreceived > e.ntransmitted)
			printf("-- somebody's printing up packets!");
		else
			printf("%d%% packetloss", (int)(((e.ntransmitted - e.nreceived) * 100)
							/ e.ntransmitted));
	}
	ft_putchar('\n');
	if (e.nreceived)
	{
		printf("rtt min/avg/max/mdev = %ld.%ld/%lu.%ld/%ld.%ld/ ms\n",
		       e.tmin / 10, e.tmin % 10,
		       (e.tsum / e.nreceived) / 10, (e.tsum / e.nreceived) % 10,
		       e.tmax / 10, e.tmax % 10);
		exit(0);
	}
	exit(1);
}

static void		ft_alarm(int sig)
{
	
	signal(SIGALRM, ft_alarm);
	if (!e.npackets || e.ntransmitted < e.npackets)
		alarm((u_int)e.interval);
	else
	{
		if (e.nreceived)
		{
			sig = 2 * e.tmax / 1000;
			if (!sig)
				sig = 1;
			if (sig > MAXWAIT)
				sig = MAXWAIT;
		}
		else
		  sig = MAXWAIT;
		signal(SIGALRM, ft_finish);
		alarm((u_int)sig);
	}
}

void			ft_signals(void)
{
	signal(SIGINT, ft_finish);
	signal(SIGALRM, ft_alarm);
}
