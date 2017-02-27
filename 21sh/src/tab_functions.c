/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 05:10:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/27 05:17:15 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void				move_tab_right(t_env *e)
{
	size_t			value;

	value = e->cursor.x + e->htab_value;
	if (value > e->sz.ws_col)
	{
		e->cursor.x = 0;
		if (e->cursor.y >= e->sz.ws_row)
		{
			tputs(ft_tgetstr("sf"), 1, ft_pchar);
			e->origin.y--;
		}
		else
			e->cursor.y++;
	}
	else if (value % e->htab_value != 0)
		e->cursor.x += (e->htab_value - (value % e->htab_value));
	else
		e->cursor.x = value;
}

void				move_tab_left(t_env *e)
{
	long			i;

	if (e->pos - 1 == e->q_pos || e->hist->cmd[e->pos - 2] == TAB)
		e->cursor.x -= e->htab_value;
	else
	{
		i = e->q_pos;
		ft_memcpy(&e->cursor, &e->origin, sizeof(e->cursor));
		while (i < e->pos - 1)
		{
			if (e->hist->cmd[i] != TAB)
				e->cursor.x++;
			else
				move_tab_right(e);
			i++;
		}
	}
}

void				highlight_tab_right(t_env *e)
{
	int				i;
	t_pos			pos;

	ft_memcpy(&pos, &e->cursor, sizeof(pos));
	ft_pos(1, e);
	ft_tgoto(&pos);
	i = (e->cursor.x) ? e->cursor.x - pos.x : e->sz.ws_col - pos.x;
	while (i-- > 0)
		tputs(ft_tgetstr("dc"), 1, ft_pchar);
	i = (e->cursor.x) ? e->cursor.x - pos.x : e->sz.ws_col - pos.x;
	write(e->fd, "        ", i);
	ft_tgoto(&e->cursor);
}

static void			highlight(int i, int limit, t_env *e)
{
	int				j;

	j = i;
	while (i-- > limit)
		tputs(ft_tgetstr("dc"), 1, ft_pchar);
	if (e->hist->cmd[e->pos + 1] == TAB)
		j++;
	write(e->fd, "        ", j);
}

void				highlight_tab_left(t_env *e)
{
	int				i;
	t_pos			pos;

	ft_memcpy(&pos, &e->cursor, sizeof(pos));
	if (e->hist->cmd[e->pos] == TAB)
	{
		ft_pos(1, e);
		ft_tgoto(&pos);
		i = (e->cursor.x) ? e->cursor.x - pos.x : e->sz.ws_col - pos.x;
		highlight(i, 1, e);
		ft_pos(-1, e);
	}
	ft_pos(-1, e);
	if (e->hist->cmd[e->pos] != TAB)
	{
		tputs(ft_tgetstr("dc"), 1, ft_pchar);
		write(e->fd, &e->hist->cmd[e->pos], 1);
		ft_tgoto(&e->cursor);
		return ;
	}
	i = (pos.x) ? pos.x - e->cursor.x : e->sz.ws_col - e->cursor.x;
	highlight(i, 0, e);
	ft_tgoto(&e->cursor);
}
