/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/16 16:34:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/26 16:40:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			ft_free_all(t_env *e)
{
	int			i;

	i = 0;
	while (e->map && e->map[i])
		free(e->map[i++]);
	if (e->map)
		free(e->map);
	e->map = NULL;
	if (e->img)
		mlx_destroy_image(e->mlx, e->img);
	e->img = NULL;
	if (e->win)
		mlx_destroy_window(e->mlx, e->win);
	e->win = NULL;
}
