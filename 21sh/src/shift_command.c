/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 02:15:20 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/27 02:57:44 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
** "mr"		Enter reverse-video mode.
** "dc"		Delete one character position at the cursor.
** "sf"		Scroll the screen one line up.
** "cr"		Move the cursor to the beginning of the line it is on.
** "me"		Turn off all appearance modes.
*/

static void		shift_right(void)
{
	if (e.cpy.cpy == 0)
		e.cpy.cpy = 1;
	if (e.cpy.cpy == 1)
		tputs(ft_tgetstr("mr"), 1, ft_pchar);
	tputs(ft_tgetstr("dc"), 1, ft_pchar);
	write(e.fd, &e.hist->cmd[e.pos.x], 1);
	e.pos.x++;
	if ((e.origin.x + e.pos.x) % e.sz.ws_col == 1)
	{
		tputs(ft_tgetstr("sf"), 1, ft_pchar);
		tputs(ft_tgetstr("cr"), 1, ft_pchar);
		e.pos.y++;
	}
}

static void		shift_left(void)
{
	if (e.cpy.cpy == 0)
		e.cpy.cpy = -1;
	if (e.cpy.cpy == -1 && e.pos.x != (size_t)e.cpy.shft)
		tputs(ft_tgetstr("mr"), 1, ft_pchar);
	if (e.hist->cmd[e.pos.x])
	{
		tputs(ft_tgetstr("dc"), 1, ft_pchar);
		write(e.fd, &e.hist->cmd[e.pos.x], 1);
		e.pos.x++;
		ft_pos(-1);
	}
	ft_pos(-1);
}


void			shift_command(void)
{
	if (e.cpy.cpy == 0)
		e.cpy.shft = e.pos.x;
	if (e.cpy.shft == (long int)e.pos.x)
		e.cpy.cpy = 0;
	if (SHFT_RIGHT && e.pos.x < ft_strlen(e.hist->cmd))
		shift_right();
	else if (SHFT_LEFT && e.pos.x > 0)
		shift_left();
	tputs(ft_tgetstr("me"), 1, ft_pchar);
}
