/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_shft_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 02:21:54 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/08 23:22:15 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		ct_sh_right(size_t size, t_env *e)
{
	if (e->cpy.cpy == 0)
		e->cpy.cpy = 1;
	if (e->cpy.cpy == 1)
		tputs(ft_tgetstr("mr"), 1, ft_pchar);
	while (e->pos < size && e->hist->cmd[e->pos] == ' ')
	{
		if (e->cpy.shft == (long int)e->pos && (e->cpy.cpy = 1))
			tputs(ft_tgetstr("mr"), 1, ft_pchar);
		tputs(ft_tgetstr("dc"), 1, ft_pchar);
		write(e->fd, &e->hist->cmd[e->pos], 1);
		ft_pos(1, e);
	}
	while (e->pos < size && e->hist->cmd[e->pos] != ' ')
	{
		if (e->cpy.shft == (long int)e->pos && (e->cpy.cpy = 1))
			tputs(ft_tgetstr("mr"), 1, ft_pchar);
		tputs(ft_tgetstr("dc"), 1, ft_pchar);
		write(e->fd, &e->hist->cmd[e->pos], 1);
		ft_pos(1, e);
	}
}

static void		highlight(t_env *e)
{
	if (e->cpy.shft > (long int)e->pos && (e->cpy.cpy = -1))
		tputs(ft_tgetstr("mr"), 1, ft_pchar);
	if (e->hist->cmd[e->pos])
	{
		tputs(ft_tgetstr("dc"), 1, ft_pchar);
		write(e->fd, &e->hist->cmd[e->pos], 1);
		ft_pos(-1, e);
	}
	else
		ft_pos(-1, e);
}

static void		ct_sh_left(t_env *e)
{
	if (e->cpy.cpy == 0)
		e->cpy.cpy = -1;
	while (e->pos > 0 && ft_memcmp(&e->cursor, &e->origin, sizeof(e->cursor)) &&
			e->hist->cmd[e->pos - 1] == ' ')
		highlight(e);
	while (e->pos > 0 && ft_memcmp(&e->cursor, &e->origin, sizeof(e->cursor)) &&
			e->hist->cmd[e->pos - 1] != ' ')
		highlight(e);
}

void			ctrl_shift_command(t_env *e)
{
	if (e->cpy.cpy == 0)
		e->cpy.shft = e->pos;
	if (e->cpy.shft == (long int)e->pos)
		e->cpy.cpy = 0;
	if (CT_SH_RI(e))
		ct_sh_right(ft_strlen(e->hist->cmd), e);
	else if (CT_SH_LE(e))
		ct_sh_left(e);
	tputs(ft_tgetstr("me"), 1, ft_pchar);
}
