/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/29 03:38:13 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/27 18:54:06 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void			move_up(t_env *e)
{
	int				hit;

	hit = e->map[(int)(e->player.pos_x + e->player.dir_x
						* e->player.speed_move)][(int)(e->player.pos_y)];
	if (hit < '1' || hit > '9')
		e->player.pos_x += e->player.dir_x * e->player.speed_move;
	hit = e->map[(int)(e->player.pos_x)][(int)(e->player.pos_y + e->player.dir_y
												* e->player.speed_move)];
	if (hit < '1' || hit > '9')
		e->player.pos_y += e->player.dir_y * e->player.speed_move;
}

static void			move_down(t_env *e)
{
	int				hit;

	hit = e->map[(int)(e->player.pos_x - e->player.dir_x
						* e->player.speed_move)][(int)e->player.pos_y];
	if (hit < '1' || hit > '9')
		e->player.pos_x -= e->player.dir_x * e->player.speed_move;
	hit = e->map[(int)e->player.pos_x][(int)(e->player.pos_y - e->player.dir_y
												* e->player.speed_move)];
	if (hit < '1' || hit > '9')
		e->player.pos_y -= e->player.dir_y * e->player.speed_move;
}

static void			move_left(t_env *e)
{
	double			old_dir;
	double			old_plane;

	old_dir = e->player.dir_x;
	old_plane = e->cam.plane_x;
	e->player.dir_x = e->player.dir_x * cos(e->player.speed_rotate)
		- e->player.dir_y * sin(e->player.speed_rotate);
	e->player.dir_y = old_dir * sin(e->player.speed_rotate)
		+ e->player.dir_y * cos(e->player.speed_rotate);
	e->cam.plane_x = e->cam.plane_x * cos(e->player.speed_rotate)
		- e->cam.plane_y * sin(e->player.speed_rotate);
	e->cam.plane_y = old_plane * sin(e->player.speed_rotate)
		+ e->cam.plane_y * cos(e->player.speed_rotate);
}

static void			move_right(t_env *e)
{
	double			old_dir;
	double			old_plane;

	old_dir = e->player.dir_x;
	old_plane = e->cam.plane_x;
	e->player.dir_x = e->player.dir_x * cos(-e->player.speed_rotate)
		- e->player.dir_y * sin(-e->player.speed_rotate);
	e->player.dir_y = old_dir * sin(-e->player.speed_rotate)
		+ e->player.dir_y * cos(-e->player.speed_rotate);
	e->cam.plane_x = e->cam.plane_x * cos(-e->player.speed_rotate)
		- e->cam.plane_y * sin(-e->player.speed_rotate);
	e->cam.plane_y = old_plane * sin(-e->player.speed_rotate)
		+ e->cam.plane_y * cos(-e->player.speed_rotate);
}

void				move(t_env *e)
{
	size_t			i;
	static t_keys	keys[] = {{UP, K_UP, &move_up},
							{DOWN, K_DOWN, &move_down},
							{LEFT, K_LEFT, &move_left},
							{RIGHT, K_RIGHT, &move_right}};

	i = 0;
	while (i < (sizeof(keys) / sizeof(keys[0])))
	{
		if ((e->keys & keys[i].flag) != 0)
			keys[i].callback(e);
		i++;
	}
}
