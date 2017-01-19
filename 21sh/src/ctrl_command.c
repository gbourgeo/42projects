/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 02:18:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/19 16:55:00 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		ctrl_right(size_t size)
{
	while (e.pos < size && e.hist->command[e.pos] == ' ')
	{
		e.pos++;
		tputs(ft_tgetstr("nd"), 1, ft_pchar);
	}
	while (e.pos < size && e.hist->command[e.pos] != ' ')
	{
		e.pos++;
		tputs(ft_tgetstr("nd"), 1, ft_pchar);
	}
}

static void		ctrl_left(void)
{
	while (e.pos > 0 && e.hist->command[e.pos - 1] == ' ')
	{
		e.pos--;
		tputs(ft_tgetstr("le"), 1, ft_pchar);
	}
	while (e.pos > 0 && e.hist->command[e.pos - 1] != ' ')
	{
		e.pos--;
		tputs(ft_tgetstr("le"), 1, ft_pchar);
	}
}

void			ctrl_command(void)
{
	if (CTRL_RIGHT)
		ctrl_right(ft_strlen(e.hist->command));
	else if (CTRL_LEFT)
		ctrl_left();
}
