/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 06:26:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/16 23:56:21 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

static void		ft_do(int nb)
{
	(void)nb;
	ioctl(0, TIOCSTI, "\n");
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
