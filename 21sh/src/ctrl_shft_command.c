/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_shft_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 02:21:54 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/27 03:08:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		ct_sh_right(size_t size)
{
	if (e.cpy.cpy == 0)
		e.cpy.cpy = 1;
	if (e.cpy.cpy == 1)
		tputs(ft_tgetstr("mr"), 1, ft_pchar);
	while (e.pos.x < size && e.hist->cmd[e.pos.x] == ' ')
	{
		if (e.cpy.shft == (long int)e.pos.x && (e.cpy.cpy = 1))
			tputs(ft_tgetstr("mr"), 1, ft_pchar);
		tputs(ft_tgetstr("dc"), 1, ft_pchar);
		write(e.fd, &e.hist->cmd[e.pos.x], 1);
		e.pos.x++;
	}
	while (e.pos.x < size && e.hist->cmd[e.pos.x] != ' ')
	{
		if (e.cpy.shft == (long int)e.pos.x && (e.cpy.cpy = 1))
			tputs(ft_tgetstr("mr"), 1, ft_pchar);
		tputs(ft_tgetstr("dc"), 1, ft_pchar);
		write(e.fd, &e.hist->cmd[e.pos.x], 1);
		e.pos.x++;
	}
}

static void		highlight(void)
{
	if (e.cpy.shft > (long int)e.pos.x && (e.cpy.cpy = -1))
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

static void		ct_sh_left(void)
{
	if (e.cpy.cpy == 0)
		e.cpy.cpy = -1;
	while (e.pos.x > 0 && e.hist->cmd[e.pos.x - 1] == ' ')
		highlight();
	while (e.pos.x > 0 && e.hist->cmd[e.pos.x - 1] != ' ')
		highlight();
}

void			ctrl_shift_command(void)
{
	if (e.cpy.cpy == 0)
		e.cpy.shft = e.pos.x;
	if (e.cpy.shft == (long int)e.pos.x)
		e.cpy.cpy = 0;
	if (CT_SH_RI)
		ct_sh_right(ft_strlen(e.hist->cmd));
	else if (CT_SH_LE)
		ct_sh_left();
	tputs(ft_tgetstr("me"), 1, ft_pchar);
}
