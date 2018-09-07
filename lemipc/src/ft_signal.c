/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 23:14:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/07 14:50:36 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** SIGKILL can't be caught.
** SIGSTOP generates an error.
*/

#include "libft.h"
#include "lemipc.h"
#include <signal.h>

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
	ft_putchar('\n');
	if (e.data != (void *)-1)
	{
		if (e.map)
			*(e.map + e.x + e.y * MAP_WIDTH) = MAP_0;
		e.data->connected--;
		if (e.data->connected > 0)
			ft_exit_client(0, err);
		ft_exit_server(0, err);
	}
	if (e.creator)
		ft_exit_server(0, err);
	ft_exit_client(0, err);
}

void		init_signal(void)
{
	int		i;

	i = 1;
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
