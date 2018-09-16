/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 06:26:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/09 19:52:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

static void		ft_do(int nb)
{
	ioctl(0, TIOCSTI, "\n");
	nb = 1;
}

void			ft_signals(void)
{
	signal(SIGHUP, &ft_do);
	signal(SIGINT, &ft_do);
	signal(SIGQUIT, &ft_do);
	signal(SIGILL, &ft_do);
	signal(SIGABRT, &ft_do);
	signal(SIGFPE, &ft_do);
	signal(SIGSEGV, &ft_do);
	signal(SIGPIPE, &ft_do);
	signal(SIGTERM, &ft_do);
	signal(SIGUSR1, &ft_do);
	signal(SIGUSR2, &ft_do);
	signal(SIGCONT, &ft_do);
	signal(SIGSTOP, &ft_do);
	signal(SIGTSTP, &ft_do);
	signal(SIGWINCH, &ft_do);
}
