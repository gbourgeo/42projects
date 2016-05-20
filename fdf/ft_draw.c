/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/23 08:35:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2015/04/02 23:50:00 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			draw(t_env *e)
{
	ft_clear_image(e);
	e->img.drawn = 0;
	if (e->proj == parallel)
		draw_parallel(e);
	else if (e->proj == isometric)
		draw_isometric(e);
	else if (e->proj == conic)
		draw_conic(e);
	mlx_put_image_to_window(e->mlx, e->win, e->img.ptr, e->img_x, e->img_y);
}
