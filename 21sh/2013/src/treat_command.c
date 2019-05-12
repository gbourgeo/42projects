/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treat_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 23:39:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/27 03:58:24 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
** "sf"		If cursor at the end of the window, scrolls the screen one line up.
**			Else, move the cursor one line down.
** "cr"		Move the cursor to the beginning of the line it is on.
*/

void			treat_command(t_env *e)
{
	rewrite_command(e);
	tputs(ft_tgetstr("sf"), 1, ft_pchar);
	tputs(ft_tgetstr("cr"), 1, ft_pchar);
	if (e->quote == 0)
	{
		if (*e->hist->cmd)
			parse_command(e);
	}
	else
	{
		ft_insert_str(&e->hist->cmd[e->hist->cmd_len], "\n", 1);
		e->hist->cmd_len += 1;
		e->pos = e->hist->cmd_len;
		e->q_pos = e->hist->cmd_len;
	}
	prompt(e);
	cursor_position(&e->origin);
	ft_memcpy(&e->cursor, &e->origin, sizeof(e->cursor));
}
