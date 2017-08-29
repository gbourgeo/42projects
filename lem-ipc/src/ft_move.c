/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 19:47:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/08/28 01:56:54 by gbourgeo         ###   ########.fr       */
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
		pos --;
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

static void	move_vert(void)
{
	if (e.y < e.target->y &&
		*(e.map + e.x + (e.y + 1) * MAP_WIDTH) == -1)
		return (move(e.x, e.y + 1));
	if (e.y > e.target->y &&
		*(e.map + e.x + (e.y - 1) * MAP_WIDTH) == -1)
		return (move(e.x, e.y - 1));
}

static void	move_horiz(void)
{
	if (e.x == e.target->x) //Move verticaly
		return (move_vert());
	
}

static void	ft_move(void)
{
	if (e.dir == -1) //Move horizontaly
	{
		if (e.x == e.target->x)
			move_vert();
		else
			move_horiz();
		if (e.x <= e.target->x && e.x < MAP_WIDTH - 1 &&
			*(e.map + (e.x + 1) + e.y * MAP_WIDTH) == -1)
			return (move(e.x + 1, e.y));
		if (e.x >= e.target->x && e.x > 0 &&
			*(e.map + (e.x - 1) + e.y * MAP_WIDTH) == -1)
			return (move(e.x - 1, e.y));
		if (e.y <= e.target->y && e.y < MAP_HEIGTH - 1 &&
			*(e.map + e.x + (e.y + 1) * MAP_WIDTH) == -1)
			return (move(e.x, e.y + 1));
		if (e.y >= e.target->y && e.y > 0 &&
			*(e.map + e.x + (e.y - 1) * MAP_WIDTH) == -1)
			return (move(e.x, e.y - 1));
	}
//	else //Move vertically
}

void		ft_move_to_target(void)
{
	printf("dist:%d\n", e.target->dist);
	if (!can_i_move())
		printf("I CANT MOVE !\n");
	else if (e.target->dist > 0)
		ft_move();
}
