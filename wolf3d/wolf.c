/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/25 12:35:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/26 17:09:49 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int			key_press(int keycode, t_env *e)
{
	if (keycode == ESC)
		ft_end("Bye.", e, EXIT_SUCCESS);
	else if (keycode == UP)
		e->keys |= 0x2;
	else if (keycode == DOWN)
		e->keys |= 0x4;
	else if (keycode == LEFT)
		e->keys |= 0x8;
	else if (keycode == RIGHT)
		e->keys |= 0x10;
	return (0);
}

static int			key_release(int keycode, t_env *e)
{
	if (keycode == ESC)
		ft_end("Bye.", e, EXIT_SUCCESS);
	else if (keycode == UP)
		e->keys &= ~0x2;
	else if (keycode == DOWN)
		e->keys &= ~0x4;
	else if (keycode == LEFT)
		e->keys &= ~0x8;
	else if (keycode == RIGHT)
		e->keys &= ~0x10;
	return (0);
}

static int			expose_hook(t_env *e)
{
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (0);
}

static int			loop_hook(t_env *e)
{
	move(e);
	draw(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	return (0);
}

void				ft_wolf(t_env *e)
{
	e->mlx = mlx_init();
	if (e->mlx == NULL)
		ft_end("wolf_3d: Failed to initialize mlx.", e, EXIT_FAILURE);
	e->win = mlx_new_window(e->mlx, WIN_WIDTH, WIN_HEIGTH, "WOLF_3D");
	if (e->win == NULL)
		ft_end("wolf_3d: Failed to open a new window.", e, EXIT_FAILURE);
	e->img = mlx_new_image(e->mlx, WIN_WIDTH, WIN_HEIGTH);
	if (e->img == NULL)
		ft_end("wolf_3d: Failed to create a new image.", e, EXIT_FAILURE);
	e->data = mlx_get_data_addr(e->img, &e->bpp, &e->sizeline, &e->endian);
	if (e->data == NULL)
		ft_end("wolf_3d: Failed to get the image address.", e, EXIT_FAILURE);
	mlx_hook(e->win, KEYPRESS, KEYPRESSMASK, &key_press, e);
	mlx_hook(e->win, KEYRELEASE, KEYRELEASEMASK, &key_release, e);
	mlx_expose_hook(e->win, &expose_hook, e);
	mlx_loop_hook(e->mlx, &loop_hook, e);
	mlx_loop(e->mlx);
}
