/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 03:37:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/27 01:52:35 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
** "sf"		Scroll the screen one line up.
** "cr"		Move the cursor to the beginning of the line it is on.
*/

void			read_command(int len)
{
	if (ft_strlen(e.hist->cmd) + len > e.hist->cmd_size)
	{
		e.hist->cmd_size += CMD_SIZE;
		if (!(e.hist->cmd = ft_realloc(e.hist->cmd, e.hist->cmd_size)))
			ft_exit_all("Malloc failed.");
	}
	ft_insert_str(e.buf, len);
	write(e.fd, &e.hist->cmd[e.pos.x], len);
	e.pos.x += len;
	if ((e.origin.x + e.pos.x) % e.sz.ws_col == 1)
	{
		tputs(ft_tgetstr("sf"), 1, ft_pchar);
		tputs(ft_tgetstr("cr"), 1, ft_pchar);
		e.pos.y++;
	}
}
