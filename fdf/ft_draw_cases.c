/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_cases.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/01 22:33:37 by gbourgeo          #+#    #+#             */
/*   Updated: 2015/03/11 15:19:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		ft_check_if_next(t_env *e, t_point *p, char next)
{
	if ((next > 0 && e->coord->z[e->i] <= 0 && e->coord->next->z[e->i] <= 0) ||
		(next < 0 && e->coord->z[e->i] <= 0 && e->coord->prev->z[e->i] <= 0) ||
		(next == 0 && e->coord->z[e->i] <= 0 && e->coord->z[e->i + 1] <= 0))
		return (ft_put_color(e, p, e->ground));
	if ((next > 0 && e->coord->z[e->i] > 0 && e->coord->next->z[e->i] > 0) ||
		(next < 0 && e->coord->z[e->i] > 0 && e->coord->prev->z[e->i] > 0) ||
		(next == 0 && e->coord->z[e->i] > 0 && e->coord->z[e->i + 1] > 0))
		return (ft_put_color(e, p, e->top));
	ft_put_color(e, p, e->mid);
}

void			ft_draw_case_one(t_env *e, t_point *p, char next)
{
	while (p->x < p->x3)
	{
		if (p->x >= 0 && p->x <= e->img.w)
		{
			p->y = p->y2 + ((p->y3 - p->y2) * (p->x - p->x2)) / (p->x3 - p->x2);
			if (p->y >= 0 && p->y <= e->img.h)
				ft_check_if_next(e, p, next);
		}
		p->x++;
	}
}

void			ft_draw_case_two(t_env *e, t_point *p, char next)
{
	while (p->x > p->x3)
	{
		if (p->x >= 0 && p->x <= e->img.w)
		{
			p->y = p->y3 + ((p->y2 - p->y3) * (p->x - p->x3)) / (p->x2 - p->x3);
			if (p->y >= 0 && p->y <= e->img.h)
				ft_check_if_next(e, p, next);
		}
		p->x--;
	}
}

void			ft_draw_case_three(t_env *e, t_point *p, char next)
{
	while (p->y > p->y3)
	{
		if (p->y >= 0 && p->y <= e->img.h)
		{
			p->x = p->x2 + ((p->x3 - p->x2) * (p->y - p->y2)) / (p->y3 - p->y2);
			if (p->x >= 0 && p->x <= e->img.w)
				ft_check_if_next(e, p, next);
		}
		p->y--;
	}
}

void			ft_draw_case_four(t_env *e, t_point *p, char next)
{
	while (p->y < p->y3)
	{
		if (p->y >= 0 && p->y <= e->img.h)
		{
			p->x = p->x3 + ((p->x2 - p->x3) * (p->y - p->y3)) / (p->y2 - p->y3);
			if (p->x >= 0 && p->x <= e->img.w)
				ft_check_if_next(e, p, next);
		}
		p->y++;
	}
}
