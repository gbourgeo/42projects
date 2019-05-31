/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 23:14:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/05/28 17:02:53 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** SIGKILL can't be caught.
** SIGSTOP generates an error.
*/

#include <unistd.h>
#include <signal.h>
#include "lemipc.h"

void			game_signal_catcher(int sig)
{
	char		*err;
	static char	*signals[] = {
		"0", "SIGUP", "SIGINT", "SIGQUIT", "SIGILL",
		"SIGTRAP", "SIGABRT", "SIGPOLL/SIGEMT",
		"SIGFPE", "SIGKILL", "SIGBUS", "SIGSEGV",
		"SIGSYS", "SIGPIPE", "SIGALRM", "SIGTERM",
		"SIGURG", "SIGSTOP", "SIGTSTP", "SIGCONT",
		"SIGCHLD", "SIGTTIN", "SIGTTOU", "SIGIO",
		"SIGXCPU", "SIGXFSZ", "SIGVTALRM", "SIGPROF",
		"SIGWINCH", "SIGINFO", "SIGUSR1", "SIGUSR2",
	};

	err = (sig >= 0 && sig < NSIG) ? signals[sig] : "Unknown signal error";
	write(2, "\n", 1);
	ft_exit(0, err, 0);
}

void			init_signal(void (*signal_catcher)(int))
{
	int i;

	i = 0;
	while (i < NSIG)
	{
		if (i != SIGWINCH && i != SIGUSR2)
			signal(i, signal_catcher);
		i++;
	}
}
