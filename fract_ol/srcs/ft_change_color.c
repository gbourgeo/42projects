/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 20:14:13 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/19 20:28:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void				ft_change_color(t_env *e, t_img *i, int keycode, int win)
{
	if (keycode == KB_FN)
		i->r += 1;
	if (keycode == KB_DEL && i->r > 1)
		i->r -= 1;
	if (keycode == KB_HOME)
		i->g += 1;
	if (keycode == KB_END && i->g > 1)
		i->g -= 1;
	if (keycode == KB_PUP)
		i->b += 1;
	if (keycode == KB_PDO && i->b > 1)
		i->b -= 1;
	if (win == 1)
		do_one_draw(e, i->type, 0, 0);
	if (win == 2)
		do_two_draw(e, i->type, 0, 0);
}
