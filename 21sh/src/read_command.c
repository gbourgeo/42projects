/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 03:37:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/08 19:01:06 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
** "sf"		Scroll the screen one line up.
** "cr"		Move the cursor to the beginning of the line it is on.
*/

void			read_command(int len, t_env *e)
{
	if (ft_strlen(e->hist->cmd) + len >= e->hist->cmd_size)
	{
		e->hist->cmd_size += CMD_SIZE;
		if (!(e->hist->cmd = ft_realloc(e->hist->cmd, e->hist->cmd_size)))
			ft_exit_all("Malloc failed.");
	}
	ft_insert_str(&e->hist->cmd[e->pos], e->buf, len);
	tputs(ft_tgetstr("cd"), 1, ft_pchar);
	ft_putstr_fd(&e->hist->cmd[e->pos], e->fd);
	ft_pos(len, e);
}
