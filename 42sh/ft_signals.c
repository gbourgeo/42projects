/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 01:21:28 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/30 22:00:35 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void		ft_break_this_signal(int signum)
{
	if (signum == SIGINT)
		ft_putchar('\n');
	if (signum == SIGTSTP)
		main(0, NULL);
}

void			ft_signals(void)
{
	signal(SIGHUP, &ft_break_this_signal);
	signal(SIGINT, &ft_break_this_signal);
	signal(SIGQUIT, &ft_break_this_signal);
	signal(SIGILL, &ft_break_this_signal);
	signal(SIGABRT, &ft_break_this_signal);
	signal(SIGFPE, &ft_break_this_signal);
	signal(SIGSEGV, &ft_break_this_signal);
	signal(SIGPIPE, &ft_break_this_signal);
	signal(SIGTERM, &ft_break_this_signal);
	signal(SIGUSR1, &ft_break_this_signal);
	signal(SIGUSR2, &ft_break_this_signal);
	signal(SIGCHLD, &ft_break_this_signal);
	signal(SIGCONT, &ft_break_this_signal);
	signal(SIGTSTP, &ft_break_this_signal);
}
