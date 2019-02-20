/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_func.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/27 12:04:22 by gbourgeo          #+#    #+#             */
/*   Updated: 2015/04/02 23:44:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			ft_directional_move(int keycode, t_env *e)
{
	e->img_x += (keycode == K_LE) ? MOVE_RATE : 0;
	e->img_x -= (keycode == K_RI) ? MOVE_RATE : 0;
	e->img_y += (keycode == K_UP) ? MOVE_RATE : 0;
	e->img_y -= (keycode == K_D) ? MOVE_RATE : 0;
	mlx_clear_window(e->mlx, e->win);
	if (e->img.drawn)
		mlx_put_image_to_window(e->mlx, e->win, e->img.ptr, e->img_x, e->img_y);
	else
		draw(e);
}

void			ft_projection_type(int keycode, t_env *e)
{
	if ((keycode == K_ONE && e->proj != parallel) ||
		(keycode == K_TWO && e->proj != conic) ||
		(keycode == K_THREE && e->proj != isometric))
	{
		if (keycode == K_ONE)
			e->proj = parallel;
		else if (keycode == K_TWO)
			e->proj = conic;
		else if (keycode == K_THREE)
			e->proj = isometric;
		mlx_clear_window(e->mlx, e->win);
		draw(e);
	}
}

void			ft_resize_image(int keycode, t_env *e)
{
	char		*data;

	e->ecart_x += (keycode == PLUS) ? ECART_RATE : 0;
	e->ecart_x -= (keycode == MINUS) ? ECART_RATE : 0;
	mlx_clear_window(e->mlx, e->win);
	mlx_destroy_image(e->mlx, e->img.ptr);
	e->img.ptr = NULL;
	e->img.w = ECART_X * (e->map_w + e->map_h + 2);
	e->img.h = (e->map_h > e->map_w) ? e->map_h + 2 : e->map_w + 2;
	e->img.h *= ECART_X;
	if (!(e->img.ptr = mlx_new_image(e->mlx, e->img.w, e->img.h)))
		ft_end("fdf: Failed to create a new_image.", e);
	data = mlx_get_data_addr(e->img.ptr, &e->bpp, &e->sizeline, &e->endian);
	if (data == NULL)
		ft_end("fdf: Failed to get_data_addr.", e);
	e->img.data = data;
	ft_putstr("New image created is ");
	ft_putnbr(e->img.w);
	ft_putstr(" width and ");
	ft_putnbr(e->img.h);
	ft_putendl(" height.");
	draw(e);
}

void			ft_change_constante(int keycode, t_env *e)
{
	if ((keycode == MULT && CSTE < 1) || (keycode == DIV && CSTE > 0))
	{
		if (CSTE < 1)
			e->cste += (keycode == MULT) ? CSTE_RATE : 0;
		if (CSTE > 0)
			e->cste -= (keycode == DIV) ? CSTE_RATE : 0;
		mlx_clear_window(e->mlx, e->win);
		draw(e);
	}
}
