/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_isometric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/03 13:23:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2015/03/23 01:12:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void			draw_x_line(t_env *e, t_point *p)
{
	p->x = p->x2;
	p->y = p->y2;
	if (p->y >= 0 && p->y <= e->img.h && p->x >= 0 && p->x <= e->img.w)
	{
		if (e->coord->z[e->i] > 0)
			ft_put_color(e, p, e->top);
		else
			ft_put_color(e, p, e->ground);
	}
	if (e->i + 1 < e->coord->len)
	{
		p->x++;
		p->x3 = p->x1 + (e->i + 1) * ECART_X;
		p->y3 = p->y1 - CSTE * e->coord->z[e->i + 1] / 2 + (e->i + 1) * ECART_Y;
		if (p->x3 - p->x2 >= ft_abs(p->y3 - p->y2))
			ft_draw_case_one(e, p, 0);
		else if (p->y2 >= p->y3)
			ft_draw_case_three(e, p, 0);
		else
			ft_draw_case_four(e, p, 0);
	}
}

static void			draw_y_line(t_env *e, t_point *p)
{
	p->x = p->x2;
	p->y = p->y2;
	p->x3 = p->x1 + (e->i - 1) * ECART_X;
	p->y3 = p->y1 - CSTE * e->coord->next->z[e->i] / 2 + (e->i + 1) * ECART_Y;
	if (p->x2 - p->x3 >= ft_abs(p->y2 - p->y3))
		ft_draw_case_two(e, p, 1);
	else if (p->y2 >= p->y3)
		ft_draw_case_three(e, p, 1);
	else
		ft_draw_case_four(e, p, 1);
}

static void			draw_lines(t_env *e, t_point *p)
{
	while (e->i < e->coord->len)
	{
		p->x2 = p->x1 + e->i * ECART_X;
		p->y2 = p->y1 - CSTE * e->coord->z[e->i] / 2 + e->i * ECART_Y;
		if (e->coord->next && e->i < e->coord->next->len)
			draw_y_line(e, p);
		draw_x_line(e, p);
		e->i++;
	}
}

void				draw_isometric(t_env *e)
{
	t_coord		*tmp;
	t_point		p;

	tmp = e->coord;
	ECART_Y = ECART_X / 2;
	p.x1 = (e->map_h + 1) * ECART_X;
	p.y1 = (e->img.h - (ECART_Y * (e->map_h + e->map_w))) / 2;
	while (e->coord)
	{
		e->i = 0;
		draw_lines(e, &p);
		p.x1 -= ECART_X;
		p.y1 += ECART_Y;
		e->coord = e->coord->next;
	}
	e->coord = tmp;
	e->img.drawn = 1;
}
