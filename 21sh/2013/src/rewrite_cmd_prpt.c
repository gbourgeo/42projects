/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rewrite_cmd_prpt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 04:15:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/27 03:59:15 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
** "cm"		Position the cursor at line l, column c.
** "cr"		Move the cursor to the beginning of the line it is on.
** "cd"		Clear the line the cursor is on, and all the lines below it.
*/

void			rewrite_command(t_env *e)
{
	long		i;
	t_pos		pos;

	i = e->pos;
	ft_memcpy(&pos, &e->cursor, sizeof(pos));
	e->pos = e->q_pos;
	ft_memcpy(&e->cursor, &e->origin, sizeof(e->cursor));
	ft_tgoto(&e->cursor);
	tputs(ft_tgetstr("cd"), 1, ft_pchar);
	while (e->hist->cmd[e->pos])
	{
		write(e->fd, &e->hist->cmd[e->pos], 1);
		ft_pos(1, e);
	}
	e->pos = i;
	ft_memcpy(&e->cursor, &pos, sizeof(e->cursor));
	ft_tgoto(&e->cursor);
	e->cpy.cpy = 0;
}
