/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/27 18:45:17 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/26 17:05:22 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void			ft_put_color(t_env *e, int x, int y, int color)
{
	char			*ptr;
	int				opp;

	opp = e->bpp / 8;
	ptr = e->data + y * e->sizeline + x * opp;
	while (opp--)
	{
		if (e->endian == e->local_endian)
		{
			if (e->endian)
				*(ptr + opp) = ((unsigned char *)(&color))[4 - y + opp];
			else
				*(ptr + opp) = ((unsigned char *)(&color))[opp];
		}
		else
		{
			if (e->endian)
				*(ptr + opp) = ((unsigned char *)(&color))[y - 1 - opp];
			else
				*(ptr + opp) = ((unsigned char *)(&color))[3 - opp];
		}
	}
}

static void			ft_print_to_image(t_env *e)
{
	int				j;

	j = 0;
	while (j < WIN_HEIGTH)
	{
		if (j < e->draw.start)
			ft_put_color(e, e->draw.x, j, e->sky);
		else if (j > e->draw.end)
			ft_put_color(e, e->draw.x, j, e->ground);
		else if (e->draw.side == 0 && e->cam.dir_x >= 0)
			ft_put_color(e, e->draw.x, j, e->north);
		else if (e->draw.side == 0 && e->cam.dir_x < 0)
			ft_put_color(e, e->draw.x, j, e->south);
		else if (e->draw.side == 1 && e->cam.dir_y <= 0)
			ft_put_color(e, e->draw.x, j, e->east);
		else
			ft_put_color(e, e->draw.x, j, e->west);
		j++;
	}
}

static void			ft_init_draw(t_env *e)
{
	e->cam.x = 2 * e->draw.x / (double)WIN_WIDTH - 1;
	e->draw.side = 0;
	e->draw.hit = 0;
	e->cam.pos_x = e->player.pos_x;
	e->cam.pos_y = e->player.pos_y;
	e->cam.dir_x = e->player.dir_x + e->cam.plane_x * e->cam.x;
	e->cam.dir_y = e->player.dir_y + e->cam.plane_y * e->cam.x;
	e->draw.map_x = (int)e->cam.pos_x;
	e->draw.map_y = (int)e->cam.pos_y;
	e->draw.dist_delta_x = sqrt(1 + pow(e->cam.dir_y, 2)
								/ pow(e->cam.dir_x, 2));
	e->draw.dist_delta_y = sqrt(1 + pow(e->cam.dir_x, 2)
								/ pow(e->cam.dir_y, 2));
}

void				draw(t_env *e)
{
	e->draw.x = 0;
	while (e->draw.x < WIN_WIDTH)
	{
		ft_init_draw(e);
		ft_raycast(e);
		ft_print_to_image(e);
		e->draw.x++;
	}
}
