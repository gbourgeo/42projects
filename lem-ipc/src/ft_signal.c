/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 18:32:33 by root              #+#    #+#             */
/*   Updated: 2016/12/12 12:51:21 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static void	catch_sig(int sig)
{
	static char	*signals[] = { "0", "SIGUP", "SIGINT", "SIGQUIT", "SIGILL",
							   "SIGTRAP", "SIGABRT", "SIGPOLL/SIGEMT", "SIGFPE",
							   "SIGKILL", "SIGBUS", "SIGSEGV", "SIGSYS",
							   "SIGPIPE", "SIGALRM", "SIGTERM", "SIGURG",
							   "SIGSTOP", "SIGTSTP", "SIGCONT", "SIGCHLD",
							   "SIGTTIN", "SIGTTOU", "SIGIO", "SIGXCPU",
							   "SIGXFSZ", "SIGVTALRM", "SIGPROF", "SIGWINCH",
							   "SIGINFO", "SIGUSR1", "SIGUSR2" };

	printf("\n");
	if (e.data != (void *)-1)
	{
		e.data->connected -= 1;
		*((int *)e.data + e.team) -= 1;
		if (e.map != (void *)-1 && e.x >= 0 && e.y >= 0)
			*(e.map + e.x + e.y * HEIGTH) = -1;
		if (e.data->connected > 0)
			ft_exit_client(0, signals[sig]);
		ft_exit_server(0, signals[sig]);
	}
	ft_exit_client(0, signals[sig]);
}

void		ft_signal(void)
{
	if (signal(SIGINT, catch_sig) == SIG_ERR)
	{
		if (e.data != (void *)-1)
		{
			e.data->connected -= 1;
			*((int *)e.data + e.team) -= 1;
			if (e.data->connected > 0)
				ft_exit_client(0, "signal");
			ft_exit_server(1, "signal");
		}
		ft_exit_client(0, "signal");
	}
}
