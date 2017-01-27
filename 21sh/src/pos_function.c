/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 01:17:54 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/27 02:34:55 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
** "do"		Move the cursor vertically down one line.
** "cr"		Move the cursor to the beginning of the line it is on.
** "nd"		Move the cursor right one column.
**
** "up"		Move the cursor vertically up one line.
** "le"		Move the cursor left one column.
*/

static void		move_right(int len, size_t size)
{
	while (len > 0 && e.pos.x < size)
	{
		if ((e.pos.y == 0 && e.origin.x + e.pos.x > e.sz.ws_col) ||
			(e.pos.y > 0 && e.pos.x > e.sz.ws_col))
		{
			tputs(ft_tgetstr("do"), 1, ft_pchar);
			tputs(ft_tgetstr("cr"), 1, ft_pchar);
			e.pos.y++;
		}
		else
			tputs(ft_tgetstr("nd"), 1, ft_pchar);
		e.pos.x++;
		len -= 1;
	}
}

static void		move_left(int len)
{
	while (len < 0 && e.pos.x > 0)
	{
		if (e.pos.y > 0 && (e.origin.x + e.pos.x) % e.sz.ws_col == 0)
		{
			tputs(ft_tgetstr("up"), 1, ft_pchar);
			ft_pos(e.sz.ws_col);
			e.pos.y--;
		}
		else
			tputs(ft_tgetstr("le"), 1, ft_pchar);
		e.pos.x--;
		len += 1;
	}
}

void			ft_pos(int len)
{
	if (len > 0)
		move_right(len, ft_strlen(e.hist->cmd));
	else if (len < 0)
		move_left(len);
}
