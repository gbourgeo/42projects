/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/29 20:45:19 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/19 00:31:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		init_check_type(t_env *e, t_img *img, char win)
{
	img->x = 0;
	img->y = 0;
	img->min_x = -2.4;
	img->max_x = 2.4;
	img->min_y = -1.5;
	img->max_y = 1.5;
	e->draw[img->type](e, img);
	mlx_put_image_to_window(e->mlx, img->win, img->img, 0, 0);
	if (win == 1)
	{
		mlx_key_hook(e->one.win, key_one_hook, e);
		mlx_mouse_hook(e->one.win, mouse_one_hook, e);
		mlx_hook(e->one.win, 6, (1L << 6), one_hook, e);
		mlx_expose_hook(e->one.win, expose_one_hook, e);
	}
	else
	{
		mlx_key_hook(e->two.win, key_two_hook, e);
		mlx_mouse_hook(e->two.win, mouse_two_hook, e);
		mlx_hook(e->two.win, 6, (1L << 6), two_hook, e);
		mlx_expose_hook(e->two.win, expose_two_hook, e);
	}
}

static void		ft_fractol_two(t_env *e)
{
	e->two.win = mlx_new_window(e->mlx, WIN_W, WIN_H, e->fract[e->two.type]);
	if (e->two.win == NULL)
		ft_end("fract'ol: Failed to open a new window.", e, 2, EXIT_FAILURE);
	e->two.img = mlx_new_image(e->mlx, WIN_W, WIN_H);
	if (e->two.img == NULL)
		ft_end("fract'ol: Failed to create a new image.", e, 2, EXIT_FAILURE);
	e->two.data = mlx_get_data_addr(e->two.img, &e->bpp, &e->sline, &e->endian);
	if (e->two.data == NULL)
		ft_end("fract'ol: Failed to get the image addr.", e, 2, EXIT_FAILURE);
	init_check_type(e, &e->two, 2);
}

void			ft_fractol(t_env *e)
{
	e->mlx = mlx_init();
	if (e->mlx == NULL)
		ft_end("fract'ol: Failed to initialize mlx.", e, 1, EXIT_FAILURE);
	e->one.win = mlx_new_window(e->mlx, WIN_W, WIN_H, e->fract[e->one.type]);
	if (e->one.win == NULL)
		ft_end("fract'ol: Failed to open a new window.", e, 1, EXIT_FAILURE);
	e->one.img = mlx_new_image(e->mlx, WIN_W, WIN_H);
	if (e->one.img == NULL)
		ft_end("fract'ol: Failed to create a new image.", e, 1, EXIT_FAILURE);
	e->one.data = mlx_get_data_addr(e->one.img, &e->bpp, &e->sline, &e->endian);
	if (e->one.data == NULL)
		ft_end("fract'ol: Failed to get the image addr.", e, 1, EXIT_FAILURE);
	init_check_type(e, &e->one, 1);
	if (e->two.type != -1)
		ft_fractol_two(e);
	mlx_loop(e->mlx);
}
