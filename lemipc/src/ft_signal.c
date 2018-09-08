/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 23:14:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/08 17:38:37 by root             ###   ########.fr       */
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
	if (e.player.board != (void *)-1)
	{
		*(e.player.map + GET_POS(e.x, e.y)) = MAP_0;
		e.player.team->total--;
		e.player.board->players--;
	}
	ft_exit_client(0, err, &e.player);
}

void		init_signal(void)
{
	int		i;

	i = 0;
	while (i < NSIG)
	{
		signal(i, catch_sig);
		i++;
	}
}
