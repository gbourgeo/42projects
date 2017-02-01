/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 02:18:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/31 17:28:06 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		ctrl_right(size_t size)
{
	while (e.pos < size && e.hist->cmd[e.pos] == ' ')
		ft_pos(1);
	while (e.pos < size && e.hist->cmd[e.pos] != ' ')
		ft_pos(1);
}

static void		ctrl_left(void)
{
	while (e.pos > 0 && e.hist->cmd[e.pos - 1] == ' ')
		ft_pos(-1);
	while (e.pos > 0 && e.hist->cmd[e.pos - 1] != ' ')
		ft_pos(-1);
/* 	if (e.pos == 0) { */
/* 		ft_putnbr(e.cursor.y); ft_putnbr(e.origin.y); ft_putnbr(e.sz.ws_row - 1); } */
}

void			ctrl_command(void)
{
	if (CTRL_RIGHT)
		ctrl_right(ft_strlen(e.hist->cmd));
	else if (CTRL_LEFT)
		ctrl_left();
}
