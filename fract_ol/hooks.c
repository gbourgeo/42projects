/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/29 21:23:08 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/19 20:20:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			do_one_draw(t_env *e, int type, int movex, int movey)
{
	e->one.type = type;
	e->one.x += movex;
	e->one.y += movey;
	ft_bzero(e->one.data, e->bpp / 8 * WIN_W * WIN_H);
	e->draw[e->one.type](e, &e->one);
	mlx_put_image_to_window(e->mlx, e->one.win, e->one.img, 0, 0);
}

int				key_one_hook(int keycode, t_env *e)
{
	if (keycode == ESC)
		ft_end("Bye.", e, 1, EXIT_SUCCESS);
	if (keycode == KB_1)
		do_one_draw(e, 0, 0, 0);
	if (keycode == KB_2)
		do_one_draw(e, 1, 0, 0);
	if (keycode == KB_3)
		do_one_draw(e, 2, 0, 0);
	if (keycode == KB_4)
		do_one_draw(e, 3, 0, 0);
	if (keycode == KB_UP)
		do_one_draw(e, e->one.type, 0, MOVE);
	if (keycode == KB_DOWN)
		do_one_draw(e, e->one.type, 0, -MOVE);
	if (keycode == KB_LEFT)
		do_one_draw(e, e->one.type, MOVE, 0);
	if (keycode == KB_RIGHT)
		do_one_draw(e, e->one.type, -MOVE, 0);
	if (keycode == KB_FN || (keycode == KB_DEL && e->one.r > 1) ||
		keycode == KB_HOME || (keycode == KB_END && e->one.g > 1) ||
		keycode == KB_PUP || (keycode == KB_PDO && e->one.b > 1))
		ft_change_color(e, &e->one, keycode, 1);
	return (0);
}

int				mouse_one_hook(int keycode, int x, int y, t_env *e)
{
	if (keycode == M_WHEEL_UP || keycode == M_WHEEL_DOWN)
	{
		e->one.rc = ((double)x - WIN_W / RATIO) / (WIN_W / RATIO);
		e->one.ic = ((double)y - WIN_H / RATIO) / (WIN_H / RATIO);
		e->one.min_x += (e->one.rc) / 4;
		e->one.max_x += (e->one.rc) / 4;
		e->one.min_y += (e->one.ic) / 4;
		e->one.max_y += (e->one.ic) / 4;
		e->one.zoom += (keycode == M_WHEEL_UP) ? ZOOM : -ZOOM;
		do_one_draw(e, e->one.type, 0, 0);
	}
	return (0);
}

int				expose_one_hook(t_env *e)
{
	if (e->one.win && e->one.img)
		mlx_put_image_to_window(e->mlx, e->one.win, e->one.img, 0, 0);
	return (0);
}

int				one_hook(int x, int y, t_env *e)
{
	if (e->one.type < 2)
	{
		e->one.rc = ((double)x - WIN_W / RATIO) / (WIN_W / RATIO);
		e->one.ic = ((double)y - WIN_H / RATIO) / (WIN_H / RATIO);
		do_one_draw(e, e->one.type, 0, 0);
	}
	return (0);
}
