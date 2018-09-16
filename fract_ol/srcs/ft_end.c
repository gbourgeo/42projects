/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/23 23:16:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/19 01:25:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		ft_destroy_img(t_env *e, t_img *i)
{
	i->type = 0;
	if (i->img != NULL)
		mlx_destroy_image(e->mlx, i->img);
	if (i->win != NULL)
		mlx_destroy_window(e->mlx, i->win);
	i->win = NULL;
}

void			ft_end(char *str, t_env *e, char win, int status)
{
	if (status == EXIT_FAILURE)
		ft_putendl_fd(str, 2);
	else
		ft_putendl_fd(str, 1);
	if (win == 1)
		ft_destroy_img(e, &e->one);
	if (win == 2)
		ft_destroy_img(e, &e->two);
	if (e->one.win == NULL && e->two.win == NULL)
		exit(status);
}
