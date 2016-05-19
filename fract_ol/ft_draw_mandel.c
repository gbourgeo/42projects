/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_mandel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/29 23:20:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/19 00:52:09 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void			calc_if_infinite(t_point *p)
{
	while (p->i < ITERATION_MAX)
	{
		p->tmp = p->zr;
		p->zr = p->tmp * p->tmp - p->zi * p->zi + p->cr;
		p->zi = 2 * p->zi * p->tmp + p->ci;
		if ((p->zr * p->zr) + (p->zi * p->zi) >= 4)
			break ;
		p->i++;
	}
}

void				ft_mandel(t_env *e, t_img *i)
{
	t_point			p;

	p.x = 0;
	while (p.x < WIN_W)
	{
		p.y = 0;
		p.cr = i->min_x + (i->max_x - i->min_x) / WIN_W * SCALE_X;
		while (p.y < WIN_H)
		{
			p.ci = i->min_y + (i->max_y - i->min_y) / WIN_H * SCALE_Y;
			p.zr = 0;
			p.zi = 0;
			p.i = 0;
			calc_if_infinite(&p);
			ft_put_color(e, &p, i);
			p.y++;
		}
		p.x++;
	}
}
