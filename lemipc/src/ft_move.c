/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 19:47:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/12 15:29:59 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include <stdio.h>

static int	can_i_move(ULL *map)
{
	int		pos;

	pos = 4;
	if (e.x == 0 || e.x == MAP_WIDTH - 1)
		pos--;
	if (e.y == 0 || e.y == MAP_HEIGTH - 1)
		pos--;
	if (e.y > 0 && *(map + GET_POS(e.x, (e.y - 1))) != MAP_0)
		pos--;
	if (e.x < MAP_WIDTH - 1 && *(map + GET_POS((e.x + 1), e.y)) != MAP_0)
		pos--;
	if (e.y < MAP_HEIGTH - 1 && *(map + GET_POS(e.x, (e.y + 1))) != MAP_0)
		pos--;
	if (e.x > 0 && *(map + GET_POS((e.x - 1), e.y)) != MAP_0)
		pos--;
	return (pos);
}

static void	move(int x, int y, ULL *map)
{
	*(map + GET_POS(e.x, e.y)) = MAP_0;
	e.x = x;
	e.y = y;
	*(map + GET_POS(e.x, e.y)) = e.team->uid;
}

void		move_verticaly(int times, ULL *map)
{
	if (e.y < e.target->y)
	{
		if (*(map + GET_POS(e.x, (e.y + 1))) == MAP_0)
			return (move(e.x, e.y + 1, map));
		if (!times)
			move_horizontaly(1, map);
	}
	else
	{
		if (*(map + GET_POS(e.x, (e.y - 1))) == MAP_0)
			return (move(e.x, e.y - 1, map));
		if (!times)
			move_horizontaly(1, map);
	}
}

void		move_horizontaly(int times, ULL *map)
{
	if (e.x > e.target->x)
	{
		if (*(map + GET_POS(e.x, e.y) - 1) == MAP_0)
			return (move(e.x - 1, e.y, map));
		if (!times)
			move_verticaly(1, map);
	}
	else
	{
		if (*(map + GET_POS(e.x, e.y) + 1) == MAP_0)
			return (move(e.x + 1, e.y, map));
		if (!times)
			move_verticaly(1, map);
	}
}

void		ft_move_to_target(ULL *map)
{
	if (!can_i_move(map))
		return ;
	else if (e.target && e.target->dist > 0)
	{
		if (e.x < e.target->x - 1 || e.x > e.target->x + 1)
			move_horizontaly(0, map);
		else
			move_verticaly(0, map);
	}
}
