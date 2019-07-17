/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 23:14:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/07/08 17:20:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** SIGKILL can't be caught.
** SIGSTOP generates an error.
*/

#include <signal.h>
#include "libft.h"
#include "lemipc.h"

void			game_signal_catcher(int sig)
{
	char		err[32];
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

	ft_strcpy(err, "signal received: ");
	if (sig >= 0 && sig < NSIG)
		ft_strcat(err, signals[sig]);
	else
		ft_strcat(err, "Unknown");
	ft_putchar('\n');
	ft_exit(0, err);
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
