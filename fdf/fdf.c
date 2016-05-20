/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/16 20:01:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/13 16:51:16 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			ft_end(char *str, t_env *e)
{
	ft_putendl_fd(str, 2);
	ft_free_all(e);
	exit(EXIT_FAILURE);
}

static int		key_hook(int keycode, t_env *e)
{
	if (keycode == ESC)
	{
		ft_free_all(e);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == K_LE || keycode == K_RI || keycode == K_UP ||
			keycode == K_D)
		ft_directional_move(keycode, e);
	else if (keycode == K_ONE || keycode == K_TWO || keycode == K_THREE)
		ft_projection_type(keycode, e);
	else if (keycode == K_FIVE)
	{
		e->img_x = 0;
		e->img_y = 0;
		mlx_put_image_to_window(e->mlx, e->win, e->img.ptr, e->img_x, e->img_y);
	}
	else if (keycode == PLUS || (keycode == MINUS && ECART_X > ECART_RATE))
		ft_resize_image(keycode, e);
	else if (keycode == MULT || keycode == DIV)
		ft_change_constante(keycode, e);
	return (0);
}

static int		expose_hook(t_env *e)
{
	if (e->img.drawn)
		mlx_put_image_to_window(e->mlx, e->win, e->img.ptr, e->img_x, e->img_y);
	else
		draw(e);
	return (0);
}

static void		ft_init_images(t_env *e)
{
	void		*ptr;
	char		*data;

	while (ECART_X * (e->map_w + e->map_h + 2) < WIN_WIDTH &&
			ECART_X * (e->map_w + 2) < WIN_HEIGTH &&
			ECART_X * (e->map_h + 2) < WIN_HEIGTH)
		ECART_X++;
	e->img.w = ECART_X * (e->map_w + e->map_h + 2);
	e->img.h = (e->map_h > e->map_w) ? e->map_h + 2 : e->map_w + 2;
	e->img.h *= ECART_X;
	if (!(ptr = mlx_new_image(e->mlx, e->img.w, e->img.h)))
		ft_end("fdf: Failed to create a new image. Size is too high.", e);
	e->img.ptr = ptr;
	data = mlx_get_data_addr(e->img.ptr, &e->bpp, &e->sizeline, &e->endian);
	if (data == NULL)
		ft_end("fdf: Failed to get data address. No memory available.", e);
	e->img.data = data;
	e->img.drawn = 0;
	ft_putstr("The image created is ");
	ft_putnbr(e->img.w);
	ft_putstr(" width and ");
	ft_putnbr(e->img.h);
	ft_putendl(" height.");
}

void			fdf(t_env *e)
{
	if ((e->mlx = mlx_init()) == NULL)
		ft_end("fdf: Failed to initialize mlx.", e);
	if (!(e->win = mlx_new_window(e->mlx, WIN_WIDTH, WIN_HEIGTH, "FDF")))
		ft_end("fdf: Failed to open a new window.", e);
	ft_putstr("Your map is ");
	ft_putnbr(e->map_w);
	ft_putstr(" width and ");
	ft_putnbr(e->map_h);
	ft_putendl(" height.");
	ft_init_images(e);
	e->ground = mlx_get_color_value(e->mlx, e->ground);
	e->top = mlx_get_color_value(e->mlx, e->top);
	e->mid = mlx_get_color_value(e->mlx, e->mid);
	e->bckgrd = mlx_get_color_value(e->mlx, BCKGRD);
	mlx_key_hook(e->win, key_hook, e);
	mlx_expose_hook(e->win, expose_hook, e);
	mlx_loop(e->mlx);
}
