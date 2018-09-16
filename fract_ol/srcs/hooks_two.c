/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 06:44:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/19 20:26:12 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			do_two_draw(t_env *e, int type, int movex, int movey)
{
	e->two.type = type;
	e->two.x += movex;
	e->two.y += movey;
	ft_bzero(e->two.data, e->bpp / 8 * WIN_W * WIN_H);
	e->draw[e->two.type](e, &e->two);
	mlx_put_image_to_window(e->mlx, e->two.win, e->two.img, 0, 0);
}

int				key_two_hook(int keycode, t_env *e)
{
	if (keycode == ESC)
		ft_end("Bye.", e, 2, EXIT_SUCCESS);
	if (keycode == KB_1)
		do_two_draw(e, 0, 0, 0);
	if (keycode == KB_2)
		do_two_draw(e, 1, 0, 0);
	if (keycode == KB_3)
		do_two_draw(e, 2, 0, 0);
	if (keycode == KB_4)
		do_two_draw(e, 3, 0, 0);
	if (keycode == KB_UP)
		do_two_draw(e, e->two.type, 0, MOVE);
	if (keycode == KB_DOWN)
		do_two_draw(e, e->two.type, 0, -MOVE);
	if (keycode == KB_LEFT)
		do_two_draw(e, e->two.type, MOVE, 0);
	if (keycode == KB_RIGHT)
		do_two_draw(e, e->two.type, -MOVE, 0);
	if (keycode == KB_FN || (keycode == KB_DEL && e->two.r > 1) ||
		keycode == KB_HOME || (keycode == KB_END && e->two.g > 1) ||
		keycode == KB_PUP || (keycode == KB_PDO && e->two.b > 1))
		ft_change_color(e, &e->two, keycode, 2);
	return (0);
}

int				mouse_two_hook(int keycode, int x, int y, t_env *e)
{
	if (keycode == M_WHEEL_UP || keycode == M_WHEEL_DOWN)
	{
		e->two.rc = ((double)x - WIN_W / RATIO) / (WIN_W / RATIO);
		e->two.ic = ((double)y - WIN_H / RATIO) / (WIN_H / RATIO);
		e->two.min_x += e->two.rc / 4;
		e->two.max_x += e->two.rc / 4;
		e->two.min_y += e->two.ic / 4;
		e->two.max_y += e->two.ic / 4;
		e->two.zoom += (keycode == M_WHEEL_UP) ? ZOOM : -ZOOM;
		do_two_draw(e, e->two.type, 0, 0);
	}
	return (0);
}

int				expose_two_hook(t_env *e)
{
	if (e->two.win && e->two.img)
		mlx_put_image_to_window(e->mlx, e->two.win, e->two.img, 0, 0);
	return (0);
}

int				two_hook(int x, int y, t_env *e)
{
	if (e->two.type < 2)
	{
		e->two.rc = ((double)x - WIN_W / RATIO) / (WIN_W / RATIO);
		e->two.ic = ((double)y - WIN_H / RATIO) / (WIN_H / RATIO);
		do_two_draw(e, e->two.type, 0, 0);
	}
	return (0);
}
