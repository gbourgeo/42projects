/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 21:41:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/01 00:12:55 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <sys/ioctl.h>

static void			sig_handler(int signum)
{
	if (signum == SIGSEGV)
		ft_exit_all("SEGFAULT !");
	if (signum == SIGINT)
		write(e.fd, "\n", 1);
	if (signum == SIGWINCH)
	{
		if (ioctl(e.fd, TIOCGWINSZ, &e.sz) == -1)
			ft_exit_all("ioctl(TIOCGWINSZ) failed.");

	}
}

void				init_signals(void)
{
	signal(SIGSEGV, &sig_handler);
	signal(SIGINT, &sig_handler);
	signal(SIGWINCH, &sig_handler);
}
