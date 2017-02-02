/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 02:18:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/02 22:31:11 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		ctrl_up(void)
{
	char		*str;

	if (e.cursor.y > e.origin.y)
	{
		e.cursor.y--;
		e.pos -= (e.sz.ws_col + 1);
		if (e.cursor.y == e.origin.y && e.cursor.x < e.origin.x)
		{
			e.cursor.x = e.origin.x;
			e.pos = 0;
		}
		str = tgoto(ft_tgetstr("cm"), e.cursor.x, e.cursor.y);
		tputs(str, 1, ft_pchar);
	}
}

static void		ctrl_down(void)
{
	char		*str;
	size_t		len;
	size_t		pos;

	if (e.cursor.y < e.sz.ws_row)
	{
		len = ft_strlen(&e.hist->cmd[e.pos]);
		if (e.cursor.x + len >= e.sz.ws_col)
		{
			e.cursor.y++;
			pos = len - (e.sz.ws_col - e.cursor.x);
			if (pos < e.cursor.x)
			{
				e.cursor.x = pos - 1;
				e.pos += len;
			}
			else
				e.pos += (e.sz.ws_col + 1);
			str = tgoto(ft_tgetstr("cm"), e.cursor.x, e.cursor.y);
			tputs(str, 1, ft_pchar);
		}
	}
}

static void		ctrl_right(size_t size)
{
	while (e.pos < size && e.hist->cmd[e.pos] == ' ')
		ft_pos(1);
	while (e.pos < size && e.hist->cmd[e.pos] != ' ')
		ft_pos(1);
}

static void		ctrl_left(void)
{
	while (e.pos > 0 && e.hist->cmd[e.pos - 1] == ' ')
		ft_pos(-1);
	while (e.pos > 0 && e.hist->cmd[e.pos - 1] != ' ')
		ft_pos(-1);
}

void			ctrl_command(void)
{
	if (CTRL_UP)
		ctrl_up();
	else if (CTRL_DOWN)
		ctrl_down();
	else if (CTRL_RIGHT)
		ctrl_right(ft_strlen(e.hist->cmd));
	else if (CTRL_LEFT)
		ctrl_left();
}
