/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 02:15:20 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/19 16:55:12 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		shift_right(void)
{
	if (e.cpy == 0)
		e.cpy = 1;
	if (e.cpy == 1)
		tputs(ft_tgetstr("mr"), 1, ft_pchar);
	tputs(ft_tgetstr("dc"), 1, ft_pchar);
	write(e.fd, &e.hist->command[e.pos], 1);
	e.pos++;
}

static void		shift_left(void)
{
	if (e.cpy == 0)
		e.cpy = -1;
	if (e.cpy == -1)
		tputs(ft_tgetstr("mr"), 1, ft_pchar);
	tputs(ft_tgetstr("dc"), 1, ft_pchar);
	write(e.fd, &e.hist->command[e.pos], 1);
	tputs(ft_tgetstr("le"), 1, ft_pchar);
	if (e.pos > 0)
	{
		e.pos--;
		if (e.pos < ft_strlen(e.hist->command) - 1)
			tputs(ft_tgetstr("le"), 1, ft_pchar);
	}
}


void			shift_command(void)
{
	if (e.cpy == 0)
		e.shft = e.pos;
	if (e.shft == (long int)e.pos)
		e.cpy = 0;
	if (SHFT_RIGHT && e.pos < ft_strlen(e.hist->command))
		shift_right();
	else if (SHFT_LEFT)
		shift_left();
	tputs(ft_tgetstr("me"), 1, ft_pchar);
}
