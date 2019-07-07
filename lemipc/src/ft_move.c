/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 19:47:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/07/07 20:40:37 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include <stdio.h>

static int	can_i_move(t_game *game)
{
	int		pos;

	pos = 4;
	if (e.x == 0 || e.x == game->board->map_width - 1)
		pos--;
	if (e.y == 0 || e.y == game->board->map_heigth - 1)
		pos--;
	if (e.y > 0 && *(game->map + GET_POS(e.x, (e.y - 1))) != MAP_0)
		pos--;
	if (e.x < game->board->map_width - 1 &&
		*(game->map + GET_POS((e.x + 1), e.y)) != MAP_0)
		pos--;
	if (e.y < game->board->map_heigth - 1 &&
		*(game->map + GET_POS(e.x, (e.y + 1))) != MAP_0)
		pos--;
	if (e.x > 0 && *(game->map + GET_POS((e.x - 1), e.y)) != MAP_0)
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

void		move_verticaly(int times, t_player *target, ULL *map)
{
	if (e.y < target->y)
	{
		if (*(map + GET_POS(e.x, (e.y + 1))) == MAP_0)
			return (move(e.x, e.y + 1, map));
		if (!times)
			move_horizontaly(1, target, map);
	}
	else
	{
		if (*(map + GET_POS(e.x, (e.y - 1))) == MAP_0)
			return (move(e.x, e.y - 1, map));
		if (!times)
			move_horizontaly(1, target, map);
	}
}

void		move_horizontaly(int times, t_player *target, ULL *map)
{
	if (e.x > target->x)
	{
		if (*(map + GET_POS(e.x, e.y) - 1) == MAP_0)
			return (move(e.x - 1, e.y, map));
		if (!times)
			move_verticaly(1, target, map);
	}
	else
	{
		if (*(map + GET_POS(e.x, e.y) + 1) == MAP_0)
			return (move(e.x + 1, e.y, map));
		if (!times)
			move_verticaly(1, target, map);
	}
}

void		ft_move_to_target(t_player *target, t_game *game)
{
	if (!can_i_move(game))
		return ;
	else if (target->dist > 0)
	{
		if (e.x < target->x - 1 || e.x > target->x + 1)
			move_horizontaly(0, target, game->map);
		else
			move_verticaly(0, target, game->map);
	}
	printf("New position: (%lld %lld)\n", e.x, e.y);
}
