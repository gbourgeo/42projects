/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termcaps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:35:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/15 05:37:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <fcntl.h>
#include <sys/ioctl.h>

void				init_termcaps(char *term_name, int ret)
{
	if (!isatty(STDIN_FILENO))
		ft_exit_all("Terminal not valid.");
	if (!ttyname(STDIN_FILENO))
		ft_exit_all("You are not connected to a terminal.");
	if (ttyslot() <= 0)
		ft_exit_all("No terminal found in database.");
	if ((data.fd = open(ttyname(STDIN_FILENO), O_RDWR)) == -1)
	{
		ft_putstr_fd("Failed to open: ", STDERR_FILENO);
		ft_exit_all(ttyname(STDIN_FILENO));
	}
	if ((term_name = ft_getenv("TERM", data.env)) == NULL)
		term_name = "xterm";
	ret = tgetent(NULL, term_name);
	if (ret == -1)
		ft_exit_all("Termcap's data base files unavailable");
	else if (ret == 0)
		ft_exit_all("Terminal not defined in database.");
	redefine_term();
	if (ioctl(data.fd, TIOCGWINSZ, &data.sz) == -1)
		ft_exit_all("ioctl(TIOCGWINSZ) failed.");
	data.sz.ws_col--;
	data.sz.ws_row--;
}
