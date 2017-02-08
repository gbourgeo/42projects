/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 21:41:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/06 21:21:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <sys/ioctl.h>

static void			sig_handler(int signum)
{
	struct winsize	win;

	if (signum == SIGSEGV)
		ft_exit_all("SEGFAULT !");
	if (signum == SIGINT)
		write(data.fd, "\n", 1);
	if (signum == SIGWINCH)
	{
		if (ioctl(data.fd, TIOCGWINSZ, &win) == -1)
			ft_exit_all("ioctl(TIOCGWINSZ) failed.");
		data.sz.ws_row = win.ws_row - 1;
		data.sz.ws_col = win.ws_col - 1;
		cursor_position(&data.cursor);
	}
}

void				init_signals(void)
{
	signal(SIGSEGV, &sig_handler);
	signal(SIGINT, &sig_handler);
	signal(SIGWINCH, &sig_handler);
}
