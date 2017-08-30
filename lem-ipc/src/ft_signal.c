/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 23:14:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/08/30 18:48:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** SIGKILL can't be caught.
** SIGSTOP generates an error.
*/

#include "lemipc.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static void	catch_sig(int sig)
{
	char		*err;
	static char	*signals[] = { "0", "SIGUP", "SIGINT", "SIGQUIT", "SIGILL",
								"SIGTRAP", "SIGABRT", "SIGPOLL/SIGEMT",
								"SIGFPE", "SIGKILL", "SIGBUS", "SIGSEGV",
								"SIGSYS", "SIGPIPE", "SIGALRM", "SIGTERM",
								"SIGURG", "SIGSTOP", "SIGTSTP", "SIGCONT",
								"SIGCHLD", "SIGTTIN", "SIGTTOU", "SIGIO",
								"SIGXCPU", "SIGXFSZ", "SIGVTALRM", "SIGPROF",
								"SIGWINCH", "SIGINFO", "SIGUSR1", "SIGUSR2" };

	err = (sig >= 0 && sig < NSIG) ? signals[sig] : "Unknown signal error";
	printf("\n");
	if (e.data != (void *)-1)
	{
		if (e.map != (void *)-1 && e.x >= 0 && e.y >= 0)
			*(e.map + e.x + e.y * MAP_WIDTH) = -1;
		e.data->connected[e.team] -= 1;
		if (ft_nb_players(e.data->connected) > 1)
			ft_exit_client(0, err);
		ft_exit_server(0, err);
	}
	ft_exit_client(0, err);
}

void		ft_signal(void)
{
	int		i;

	i = 1;
	printf("Initializing SIGNALS...\n");
	while (i < NSIG)
	{
		if (i != SIGKILL && i != SIGSTOP && i != SIGWINCH)
		{
			if (signal(i, catch_sig) == SIG_ERR)
				ft_exit(1, "signal");
		}
		i++;
	}
}
