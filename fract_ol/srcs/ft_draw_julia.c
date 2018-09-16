/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_julia.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/09 18:37:24 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/19 01:21:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void			calc_if_infinite(t_point *p, t_img *i)
{
	while (p->i < ITERATION_MAX)
	{
		p->tmp = p->zr;
		p->zr = p->tmp * p->tmp - p->zi * p->zi + i->rc;
		p->zi = 2 * p->tmp * p->zi + i->ic;
		if ((p->zr * p->zr) + (p->zi * p->zi) >= 4)
			break ;
		p->i++;
	}
}

void				ft_julia(t_env *e, t_img *i)
{
	t_point			p;

	p.x = 0;
	while (p.x < WIN_W)
	{
		p.y = 0;
		p.cr = i->min_x + (i->max_x - i->min_x) / WIN_H * SCALE_X;
		while (p.y < WIN_H)
		{
			p.zr = p.cr;
			p.zi = i->min_y + (i->max_y - i->min_y) / WIN_H * SCALE_Y;
			p.i = 0;
			calc_if_infinite(&p, i);
			ft_put_color(e, &p, i);
			p.y++;
		}
		p.x++;
	}
}
