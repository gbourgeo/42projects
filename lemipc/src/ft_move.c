/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 19:47:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/08/30 21:25:35 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include <stdio.h>

static int	can_i_move(void)
{
	int		pos;

	pos = 4;
	if (e.x == 0 || e.x == MAP_WIDTH - 1)
		pos--;
	if (e.y == 0 || e.y == MAP_HEIGTH - 1)
		pos--;
	if (e.y > 0 && *(e.map + e.x + (e.y - 1) * MAP_WIDTH) != -1)
		pos--;
	if (e.x < MAP_WIDTH - 1 && *(e.map + (e.x + 1) + e.y * MAP_WIDTH) != -1)
		pos--;
	if (e.y < MAP_HEIGTH - 1 && *(e.map + e.x + (e.y + 1) * MAP_WIDTH) != -1)
		pos--;
	if (e.x > 0 && *(e.map + (e.x - 1) + e.y * MAP_WIDTH) != -1)
		pos--;
	return (pos);
}

static void	move(int x, int y)
{
	*(e.map + e.x + e.y * MAP_WIDTH) = -1;
	e.x = x;
	e.y = y;
	*(e.map + e.x + e.y * MAP_WIDTH) = e.team;
}

void		move_verticaly(int times)
{
	if (e.y < e.target->y)
	{
		if (*(e.map + e.x + (e.y + 1) * MAP_WIDTH) == -1)
			return (move(e.x, e.y + 1));
		if (!times)
			move_horizontaly(1);
	}
	else
	{
		if (*(e.map + e.x + (e.y - 1) * MAP_WIDTH) == -1)
			return (move(e.x, e.y - 1));
		if (!times)
			move_horizontaly(1);
	}
}

void		move_horizontaly(int times)
{
	if (e.x > e.target->x)
	{
		if (*(e.map + e.x + e.y * MAP_WIDTH - 1) == -1)
			return (move(e.x - 1, e.y));
		if (!times)
			move_verticaly(1);
	}
	else
	{
		if (*(e.map + e.x + e.y * MAP_WIDTH + 1) == -1)
			return (move(e.x + 1, e.y));
		if (!times)
			move_verticaly(1);
	}
}

void		ft_move_to_target(void)
{
	if (!can_i_move())
		return ;
	else if (e.target && e.target->dist > 0)
	{
		if (e.x < e.target->x - 1 || e.x > e.target->x + 1)
			move_horizontaly(0);
		else
			move_verticaly(0);
	}
}
