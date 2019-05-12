/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 02:15:20 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/27 06:13:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
** "mr"		Enter reverse-video mode->
** "dc"		Delete one character position at the cursor.
** "sf"		Scroll the screen one line up.
** "cr"		Move the cursor to the beginning of the line it is on.
** "me"		Turn off all appearance modes.
*/

static void		shift_right(t_env *e)
{
	if (e->pos < e->hist->cmd_len)
	{
		if (e->cpy.cpy == 0)
			e->cpy.cpy = 1;
		if (e->cpy.cpy == 1)
			tputs(ft_tgetstr("mr"), 1, ft_pchar);
		if (e->hist->cmd[e->pos] != TAB)
		{
			tputs(ft_tgetstr("dc"), 1, ft_pchar);
			write(e->fd, &e->hist->cmd[e->pos], 1);
			ft_pos(1, e);
		}
		else
			highlight_tab_right(e);
		if (e->cpy.shft == e->pos)
			rewrite_command(e);
	}
}

static void		shift_left(t_env *e)
{
	if (e->pos > e->q_pos &&
		ft_memcmp(&e->cursor, &e->origin, sizeof(e->cursor)))
	{
		if (e->cpy.cpy == 0)
			e->cpy.cpy = -1;
		if (e->cpy.cpy == -1 && e->cpy.shft != e->pos)
			tputs(ft_tgetstr("mr"), 1, ft_pchar);
		tputs(ft_tgetstr("dc"), 1, ft_pchar);
		write(e->fd, &e->hist->cmd[e->pos], 1);
		if (e->hist->cmd[e->pos] != TAB)
		{
			if (e->hist->cmd[e->pos - 1] != TAB)
				ft_pos(-1, e);
			else
				highlight_tab_left(e);
		}
		else
			highlight_tab_left(e);
	}
}

static void		shift_up(t_env *e)
{
	size_t		i;

	i = 0;
	while (i++ < e->sz.ws_col + 1 && e->pos > e->q_pos)
	{
		if (e->cpy.cpy == 0)
			e->cpy.shft = e->pos;
		if (e->cpy.shft == e->pos)
			e->cpy.cpy = 0;
		shift_left(e);
	}
}

static void		shift_down(t_env *e)
{
	size_t		i;
	size_t		len;

	i = 0;
	len = ft_strlen(&e->hist->cmd[e->pos]);
	while (i++ < e->sz.ws_col + 1 && e->hist->cmd[e->pos])
	{
		if (e->cpy.cpy == 0)
			e->cpy.shft = e->pos;
		if (e->cpy.shft == e->pos)
			e->cpy.cpy = 0;
		shift_right(e);
	}
}

void			shift_command(t_env *e)
{
	if (e->cpy.cpy == 0)
		e->cpy.shft = e->pos;
	if (e->cpy.shft == e->pos)
		e->cpy.cpy = 0;
	if (SHFT_UP(e))
		shift_up(e);
	else if (SHFT_DOWN(e))
		shift_down(e);
	else if (SHFT_RIGHT(e))
		shift_right(e);
	else if (SHFT_LEFT(e))
		shift_left(e);
	tputs(ft_tgetstr("me"), 1, ft_pchar);
}
