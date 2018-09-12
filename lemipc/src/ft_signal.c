/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 23:14:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/12 15:47:37 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** SIGKILL can't be caught.
** SIGSTOP generates an error.
*/

#include "libft.h"
#include "lemipc.h"
#include <signal.h>

void			game_signal_catcher(int sig)
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
	ft_putchar('\n');
	ft_exit(0, err);
}

void			mapper_signal_catcher(int sig)
{
	(void)sig;
	ft_restore_term(&e.child.term);
	ft_exit_child(0, "signal caugth");
}

void			init_signal(void (*signal_catcher)(int))
{
	int			i;

	i = 0;
	while (i < NSIG)
	{
		if (i != SIGWINCH)
			signal(i, signal_catcher);
		i++;
	}
}
