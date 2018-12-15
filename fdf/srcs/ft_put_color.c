/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 09:38:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2015/03/03 19:36:53 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void				ft_put_color(t_env *e, t_point *point, int color)
{
	char			*ptr;
	int				opp;

	opp = e->bpp / 8;
	ptr = e->img.data + point->y * e->sizeline + point->x * opp;
	while (opp--)
	{
		if (e->endian == e->local_endian)
		{
			if (e->endian)
				*(ptr + opp) = ((unsigned char *)(&color))[4 - point->y + opp];
			else
				*(ptr + opp) = ((unsigned char *)(&color))[opp];
		}
		else
		{
			if (e->endian)
				*(ptr + opp) = ((unsigned char *)(&color))[point->y - 1 - opp];
			else
				*(ptr + opp) = ((unsigned char *)(&color))[3 - opp];
		}
	}
}
