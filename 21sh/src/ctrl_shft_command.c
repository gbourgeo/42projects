/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_shft_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 02:21:54 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/19 16:55:25 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		ct_sh_right(size_t size)
{
	if (e.cpy == 0)
		e.cpy = 1;
	if (e.cpy == 1)
		tputs(ft_tgetstr("mr"), 1, ft_pchar);
	while (e.pos < size && e.hist->command[e.pos] == ' ')
	{
		if (e.shft == (long int)e.pos && (e.cpy = 1))
			tputs(ft_tgetstr("mr"), 1, ft_pchar);
		tputs(ft_tgetstr("dc"), 1, ft_pchar);
		write(e.fd, &e.hist->command[e.pos], 1);
		e.pos++;
	}
	while (e.pos < size && e.hist->command[e.pos] != ' ')
	{
		if (e.shft == (long int)e.pos && (e.cpy = 1))
			tputs(ft_tgetstr("mr"), 1, ft_pchar);
		tputs(ft_tgetstr("dc"), 1, ft_pchar);
		write(e.fd, &e.hist->command[e.pos], 1);
		e.pos++;
	}
}

static void		highlight(size_t size)
{
	if (e.shft == (long int)e.pos && (e.cpy = -1))
		tputs(ft_tgetstr("mr"), 1, ft_pchar);
	tputs(ft_tgetstr("dc"), 1, ft_pchar);
	write(e.fd, &e.hist->command[e.pos], 1);
	tputs(ft_tgetstr("le"), 1, ft_pchar);
	if (e.pos > 0)
	{
		e.pos--;
		if (e.pos < size - 1)
			tputs(ft_tgetstr("le"), 1, ft_pchar);
	}
}

static void		ct_sh_left(size_t size)
{
	if (e.cpy == 0)
		e.cpy = -1;
	if (e.cpy == -1)
		tputs(ft_tgetstr("mr"), 1, ft_pchar);
	while (e.pos > 0 && e.hist->command[e.pos - 1] == ' ')
		highlight(size);
	while (e.pos > 0 && e.hist->command[e.pos - 1] != ' ')
		highlight(size);
}

void			ctrl_shift_command(void)
{
	if (e.cpy == 0)
		e.shft = e.pos;
	if (e.shft == (long int)e.pos)
		e.cpy = 0;
	if (CT_SH_RI)
		ct_sh_right(ft_strlen(e.hist->command));
	else if (CT_SH_LE)
		ct_sh_left(ft_strlen(e.hist->command));
	tputs(ft_tgetstr("me"), 1, ft_pchar);
}
