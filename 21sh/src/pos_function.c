/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 01:17:54 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/15 22:03:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
** "sf"		Scroll the creen one line up.
** "nd"		Move the cursor right one column.
**
** "up"		Move the cursor vertically up one line.
** "le"		Move the cursor left one column.
*/

static void		check_command_len(int len, t_env *e)
{
	size_t		y;

	if (e->hist->cmd[e->pos + len] &&
		(e->cursor.x + ft_strlen(&e->hist->cmd[e->pos])) % e->sz.ws_col == 1)
	{
		y = (e->cursor.x + ft_strlen(&e->hist->cmd[e->pos])) / e->sz.ws_col;
		while (e->cursor.y + y > e->sz.ws_row)
		{
			tputs(ft_tgetstr("sf"), 1, ft_pchar);
			e->origin.y--;
			e->cursor.y--;
		}
	}
}

static void		move_right(int len, t_env *e)
{
	while (len > 0 && e->pos < e->hist->cmd_len)
	{
		check_command_len(len, e);
		if (e->cursor.x == e->sz.ws_col || e->hist->cmd[e->pos] == '\n')
		{
			if (e->cursor.y >= e->sz.ws_row)
			{
				if (e->hist->cmd[e->pos] != '\n')
					tputs(ft_tgetstr("sf"), 1, ft_pchar);
				e->origin.y--;
			}
			else
				e->cursor.y++;
			e->cursor.x = 0;
		}
		else
			e->cursor.x++;
		e->pos++;
		len -= 1;
	}
	ft_tgoto(&e->cursor);
}

static size_t	find_pos(t_env *e)
{
	size_t		pos;

	pos = e->pos - 1;
	while (pos > 0 && e->hist->cmd[pos - 1] != '\n')
		pos--;
	return (e->pos - pos - 1);
}

static void		move_left(int len, t_env *e)
{
	while (len < 0 && e->pos > e->q_pos)
	{
		if (!ft_memcmp(&e->cursor, &e->origin, sizeof(e->cursor)))
			break ;
		if (e->cursor.x == 0)
		{
			e->cursor.y--;
			if (e->hist->cmd[e->pos - 1] != '\n')
				e->cursor.x = e->sz.ws_col;
			else if (e->cursor.y == e->origin.y)
				e->cursor.x = e->origin.x + e->pos - 1;
			else
				e->cursor.x = find_pos(e);
		}
		else
			e->cursor.x--;
		e->pos--;
		len += 1;
	}
	ft_tgoto(&e->cursor);
}

void			ft_pos(int len, t_env *e)
{
	if (len > 0)
		move_right(len, e);
	else if (len < 0)
		move_left(len, e);
}
