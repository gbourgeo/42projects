/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 02:18:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/27 02:18:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		ctrl_right(size_t size)
{
	while (e.pos.x < size && e.hist->cmd[e.pos.x] == ' ')
	{
//		e.pos.x++;
		ft_pos(1);
	}
	while (e.pos.x < size && e.hist->cmd[e.pos.x] != ' ')
	{
//		e.pos.x++;
		ft_pos(1);
	}
}

static void		ctrl_left(void)
{
	while (e.pos.x > 0 && e.hist->cmd[e.pos.x - 1] == ' ')
	{
//		e.pos.x--;
		ft_pos(-1);
	}
	while (e.pos.x > 0 && e.hist->cmd[e.pos.x - 1] != ' ')
	{
//		e.pos.x--;
		ft_pos(-1);
	}
}

void			ctrl_command(void)
{
	if (CTRL_RIGHT)
		ctrl_right(ft_strlen(e.hist->cmd));
	else if (CTRL_LEFT)
		ctrl_left();
}
