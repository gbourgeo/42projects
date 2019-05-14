/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 23:14:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/05/14 17:02:31 by gbourgeo         ###   ########.fr       */
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
	ft_exit(0, err, 0);
}

void			init_signal(void (*signal_catcher)(int))
{
	signal(SIGINT, signal_catcher);
	signal(SIGSEGV, signal_catcher);
	signal(SIGBUS, signal_catcher);
}
