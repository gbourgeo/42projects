/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 02:18:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/08 23:22:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		ctrl_up(t_env *e)
{
	char		*str;

	if (e->cursor.y > e->origin.y)
	{
		e->cursor.y--;
		e->pos -= (e->sz.ws_col + 1);
		if (e->cursor.y == e->origin.y && e->cursor.x < e->origin.x)
		{
			e->cursor.x = e->origin.x;
			e->pos = 0;
		}
		str = tgoto(ft_tgetstr("cm"), e->cursor.x, e->cursor.y);
		tputs(str, 1, ft_pchar);
	}
}

static void		ctrl_down(t_env *e)
{
	char		*str;
	size_t		len;
	size_t		pos;

	if (e->cursor.y < e->sz.ws_row)
	{
		len = ft_strlen(&e->hist->cmd[e->pos]);
		if (e->cursor.x + len >= e->sz.ws_col)
		{
			e->cursor.y++;
			pos = len - (e->sz.ws_col - e->cursor.x);
			if (pos < e->cursor.x)
			{
				e->cursor.x = pos - 1;
				e->pos += len;
			}
			else
				e->pos += (e->sz.ws_col + 1);
			str = tgoto(ft_tgetstr("cm"), e->cursor.x, e->cursor.y);
			tputs(str, 1, ft_pchar);
		}
	}
}

static void		ctrl_right(size_t size, t_env *e)
{
	while (e->pos < size && e->hist->cmd[e->pos] == ' ')
		ft_pos(1, e);
	while (e->pos < size && e->hist->cmd[e->pos] != ' ')
		ft_pos(1, e);
}

static void		ctrl_left(t_env *e)
{
	while (e->pos > 0 && ft_memcmp(&e->cursor, &e->origin, sizeof(e->cursor)) &&
			e->hist->cmd[e->pos - 1] == ' ')
		ft_pos(-1, e);
	while (e->pos > 0 && ft_memcmp(&e->cursor, &e->origin, sizeof(e->cursor)) &&
			e->hist->cmd[e->pos - 1] != ' ')
		ft_pos(-1, e);
}

void			ctrl_command(t_env *e)
{
	if (CTRL_UP(e))
		ctrl_up(e);
	else if (CTRL_DOWN(e))
		ctrl_down(e);
	else if (CTRL_RIGHT(e))
		ctrl_right(ft_strlen(e->hist->cmd), e);
	else if (CTRL_LEFT(e))
		ctrl_left(e);
}
