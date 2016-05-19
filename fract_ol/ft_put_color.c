/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/29 23:50:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/18 22:45:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int			ft_find_color(t_point *p, t_img *i)
{
	int				color;

	if (p->i >= ITERATION_MAX)
		return (0);
	((unsigned char *)(&color))[0] = sin(p->i / i->b) * 255;
	((unsigned char *)(&color))[1] = sin(p->i / i->g) * 255;
	((unsigned char *)(&color))[2] = sin(p->i / i->r) * 255;
	return (color);
}

void				ft_put_color(t_env *e, t_point *p, t_img *i)
{
	char			*ptr;
	int				opp;
	int				color;

	opp = e->bpp / 8;
	ptr = i->data + p->y * e->sline + p->x * opp;
	color = ft_find_color(p, i);
	while (opp--)
	{
		if (e->endian == e->local_endian)
		{
			if (e->endian)
				*(ptr + opp) = ((unsigned char *)(&color))[4 - p->y + opp];
			else
				*(ptr + opp) = ((unsigned char *)(&color))[opp];
		}
		else
		{
			if (e->endian)
				*(ptr + opp) = ((unsigned char *)(&color))[p->y - 1 - opp];
			else
				*(ptr + opp) = ((unsigned char *)(&color))[3 - opp];
		}
	}
}
