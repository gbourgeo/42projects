/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 01:17:54 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/31 23:16:13 by gbourgeo         ###   ########.fr       */
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

static void		check_command_len(int len)
{
	size_t		y;

	if (e.hist->cmd[e.pos + len] &&
		(e.cursor.x + ft_strlen(&e.hist->cmd[e.pos])) % e.sz.ws_col == 1)
	{
		y = (e.cursor.x + ft_strlen(&e.hist->cmd[e.pos])) / e.sz.ws_col;
		while (e.cursor.y + y > e.sz.ws_row)
		{
			tputs(ft_tgetstr("sf"), 1, ft_pchar);
			e.origin.y--;
			e.cursor.y--;
		}
	}
}

static void		move_right(int len, size_t size, char *str)
{
	while (len > 0 && e.pos < size)
	{
		check_command_len(len);
		if (e.cursor.x == e.sz.ws_col)
		{
			if (e.cursor.y >= e.sz.ws_row)
			{
				tputs(ft_tgetstr("sf"), 1, ft_pchar);
				e.origin.y--;
			}
			else
				e.cursor.y++;
			e.cursor.x = 0;
		}
		else
			e.cursor.x++;
		e.pos++;
		len -= 1;
	}
	str = tgoto(ft_tgetstr("cm"), e.cursor.x, e.cursor.y);
	tputs(str, 1, ft_pchar);
}

static void		move_left(int len, char *str)
{
	while (len < 0 && e.pos > 0)
	{
		if (e.cursor.x == 0)
		{
			e.cursor.x = e.sz.ws_col;
			e.cursor.y--;
		}
		else
			e.cursor.x--;
		e.pos--;
		len += 1;
	}
	str = tgoto(ft_tgetstr("cm"), e.cursor.x, e.cursor.y);
	tputs(str, 1, ft_pchar);
}

void			ft_pos(int len)
{
	if (len > 0)
		move_right(len, ft_strlen(e.hist->cmd), NULL);
	else if (len < 0)
		move_left(len, NULL);
}
