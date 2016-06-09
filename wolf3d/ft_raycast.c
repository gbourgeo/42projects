/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/27 18:51:21 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/27 18:45:38 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void			calc_step(t_env *e)
{
	if (e->cam.dir_x < 0)
	{
		e->draw.step_x = -1;
		e->draw.dist_side_x = (e->cam.pos_x - (double)e->draw.map_x)
			* e->draw.dist_delta_x;
	}
	else
	{
		e->draw.step_x = 1;
		e->draw.dist_side_x = ((double)e->draw.map_x + 1.0 - e->cam.pos_x)
			* e->draw.dist_delta_x;
	}
	if (e->cam.dir_y < 0)
	{
		e->draw.step_y = -1;
		e->draw.dist_side_y = (e->cam.pos_y - (double)e->draw.map_y)
			* e->draw.dist_delta_y;
	}
	else
	{
		e->draw.step_y = 1;
		e->draw.dist_side_y = ((double)e->draw.map_y + 1.0 - e->cam.pos_y)
			* e->draw.dist_delta_y;
	}
}

static void			calc_side(t_env *e)
{
	while (e->draw.hit == 0)
	{
		if (e->draw.dist_side_x < e->draw.dist_side_y)
		{
			e->draw.dist_side_x += e->draw.dist_delta_x;
			e->draw.map_x += e->draw.step_x;
			e->draw.side = 0;
		}
		else
		{
			e->draw.dist_side_y += e->draw.dist_delta_y;
			e->draw.map_y += e->draw.step_y;
			e->draw.side = 1;
		}
		if (e->map[e->draw.map_x][e->draw.map_y] != '0')
			e->draw.hit = 1;
	}
}

static void			calc_dist(t_env *e)
{
	if (e->draw.side == 0)
		e->cam.dist_wall = fabs((e->draw.map_x - e->cam.pos_x
								+ (1 - e->draw.step_x) / 2)
								/ e->cam.dir_x);
	else
		e->cam.dist_wall = fabs((e->draw.map_y - e->cam.pos_y
								+ (1 - e->draw.step_y) / 2)
								/ e->cam.dir_y);
	if (e->cam.dist_wall <= 0.005)
		e->cam.dist_wall = 0.005;
	e->draw.height = fabs(WIN_HEIGTH / e->cam.dist_wall);
	e->draw.start = (-e->draw.height / 2) + WIN_HEIGTH / 2;
	if (e->draw.start < 0)
		e->draw.start = 0;
	e->draw.end = e->draw.height / 2 + WIN_HEIGTH / 2;
	if (e->draw.end >= WIN_HEIGTH)
		e->draw.end = WIN_HEIGTH;
}

static void			calc_height(t_env *e)
{
	e->draw.height = fabs(WIN_HEIGTH / e->cam.dist_wall);
	if ((e->draw.start = -e->draw.height / 2 + WIN_HEIGTH / 2) < 0)
		e->draw.start = 0;
	if ((e->draw.end = e->draw.height / 2 + WIN_HEIGTH / 2) >= WIN_HEIGTH)
		e->draw.end = WIN_HEIGTH - 1;
}

void				ft_raycast(t_env *e)
{
	calc_step(e);
	calc_side(e);
	calc_dist(e);
	calc_height(e);
}
