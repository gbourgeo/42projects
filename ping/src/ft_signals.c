/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/09 14:23:13 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/28 23:27:18 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include <signal.h>
#include <stdio.h>

/*
** void			ft_alarm(int sig)
** {
** 	ft_pinger();
** 	signal(SIGALRM, ft_alarm);
** 	if (!e.npackets || e.ntransmitted < e.npackets)
** 		alarm((u_int)e.interval);
** 	else
** 	{
** 		if (e.nreceived)
** 		{
** 			sig = 2 * e.tmax / 1000;
** 			if (!sig)
** 				sig = 1;
** 			if (sig > MAXWAIT)
** 				sig = MAXWAIT;
** 		}
** 		else
** 			sig = MAXWAIT;
** 		signal(SIGALRM, ft_finish);
** 		alarm((u_int)sig);
** 	}
** }
*/

static void		ft_aff_ntransmitted(void)
{
	if (e.nreceived > e.ntransmitted)
		printf("-- somebody's printing up packets!");
	else
		printf("%d%% packet loss, ",
				(int)(((e.ntransmitted - e.nreceived) * 100) / e.ntransmitted));
}

static void		ft_aff_nreceived(void)
{
	printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n",
			e.tmin,
			(e.tmax + e.tmin) / 2,
			e.tmax,
			(e.tmax - e.tmin) / 2);
	exit(0);
}

void			ft_finish(int sig)
{
	(void)sig;
	signal(SIGINT, SIG_IGN);
	if ((e.start_time.tv_usec -= e.start.tv_usec) < 0)
	{
		--e.start_time.tv_sec;
		e.start_time.tv_usec += 1000000;
	}
	e.start_time.tv_sec -= e.start.tv_sec;
	printf("\n--- %s ping statistics ---\n", e.hostname);
	printf("%ld packets transmitted, ", e.ntransmitted);
	printf("%ld received, ", e.nreceived);
	if (e.nerrors)
		printf("+%ld errors, ", e.nerrors);
	if (e.ntransmitted)
		ft_aff_ntransmitted();
	printf("time %ldms\n", 1000 * e.start_time.tv_sec +
			e.start_time.tv_usec / 1000);
	if (e.nreceived)
		ft_aff_nreceived();
	printf("\n");
	exit(1);
}

void			ft_alarm(int sig)
{
	(void)sig;
	ft_pinger();
	signal(SIGALRM, ft_alarm);
	alarm((u_int)e.interval);
}

void			ft_signals(void)
{
	signal(SIGINT, ft_finish);
	signal(SIGALRM, ft_alarm);
}
