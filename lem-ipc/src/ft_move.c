/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 19:47:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/19 22:27:49 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include <stdio.h>

static int	can_i_move(void)
{
	int		pos;

	pos = 4;
	if (e.x == 0 || e.x == WIDTH - 1)
		pos--;
	if (e.y == 0 || e.y == HEIGTH - 1)
		pos--;
	if (e.y > 0 && *(e.map + e.x + (e.y - 1) * WIDTH) != 0)
		pos--;
	if (e.x < WIDTH - 1 && *(e.map + (e.x + 1) + e.y * WIDTH) != 0)
		pos --;
	if (e.y < HEIGTH - 1 && *(e.map + e.x + (e.y + 1) * WIDTH) != 0)
		pos--;
	if (e.x > 0 && *(e.map + (e.x - 1) + e.y * WIDTH) != 0)
		pos--;
	return (pos);
}

static void	move(int x, int y)
{
	*(e.map + e.x + e.y * WIDTH) = 0;
	e.x = x;
	e.y = y;
	*(e.map + e.x + e.y * WIDTH) = e.team;
}

static int	move_vert(void)
{
	if (e.y < e.target.y &&
		*(e.map + e.x + (e.y + 1) * WIDTH) == 0)
		return (move(e.x, e.y + 1));
	if (e.y > e.target.y &&
		*(e.map + e.x + (e.y - 1) * WIDTH) == 0)
		return (move(e.x, e.y - 1));
	return (0);
}

static int	move_horiz(void)
{
	if (e.x == e.target.x) //Move verticaly
		return (move_vert());
	
	return (0);
}

static void	ft_move(void)
{
	if (e.dir == 0) //Move horizontaly
	{
		if (e.x == e.target.x)
			move_vert();
		else
			move_horiz();
		if (e.x <= e.target.x && e.x < WIDTH - 1 &&
			*(e.map + (e.x + 1) + e.y * WIDTH) == 0)
			return (move(e.x + 1, e.y));
		if (e.x >= e.target.x && e.x > 0 &&
			*(e.map + (e.x - 1) + e.y * WIDTH) == 0)
			return (move(e.x - 1, e.y));
		if (e.y <= e.target.y && e.y < HEIGTH - 1 &&
			*(e.map + e.x + (e.y + 1) * WIDTH) == 0)
			return (move(e.x, e.y + 1));
		if (e.y >= e.target.y && e.y > 0 &&
			*(e.map + e.x + (e.y - 1) * WIDTH) == 0)
			return (move(e.x, e.y - 1));
	}
	else //Move vertically
}

void		ft_move_to_target(void)
{
	e.target.dist = (e.x > e.target.x) ? e.x - e.target.x : e.target.x - e.x;
	e.target.dist += (e.y > e.target.y) ? e.y - e.target.y : e.target.y - e.y;
	printf("dist:%d ", e.target.dist);
//	e.target.dist -= 2;
	printf("dist:%d\n", e.target.dist);
	if (!can_i_move())
		printf("I CANT MOVE !\n");
	else if (e.target.dist > 0)
		ft_move();
}
