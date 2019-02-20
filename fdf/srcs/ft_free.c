/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/16 16:34:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2015/03/03 20:34:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		ft_free_map(t_map **map)
{
	if (map && *map)
	{
		if ((*map)->next)
			ft_free_map(&(*map)->next);
		if ((*map)->line)
			free((*map)->line);
		(*map)->next = NULL;
		free(*map);
		*map = NULL;
	}
}

static void	ft_free_coord(t_coord **coord)
{
	if (coord && *coord)
	{
		if ((*coord)->next)
			ft_free_coord(&(*coord)->next);
		if ((*coord)->z)
		{
			ft_bzero((*coord)->z, (*coord)->len);
			free((*coord)->z);
		}
		(*coord)->len = 0;
		(*coord)->z = NULL;
		(*coord)->next = NULL;
		free(*coord);
		*coord = NULL;
	}
}

void		ft_free_all(t_env *e)
{
	e->i = 0;
	if (e->mlx && e->img.ptr)
		mlx_destroy_image(e->mlx, e->img.ptr);
	e->img.ptr = NULL;
	e->img.data = NULL;
	if (e->win)
		mlx_destroy_window(e->mlx, e->win);
	e->win = NULL;
	ft_free_coord(&e->coord);
	e->ground = 0;
	e->top = 0;
	e->mid = 0;
	e->ecart_x = 0;
	e->ecart_y = 0;
	e->img_x = 0;
	e->img_y = 0;
}
