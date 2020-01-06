/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_star.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 22:17:53 by dbaffier          #+#    #+#             */
/*   Updated: 2019/10/12 23:11:28 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void	conv_star(t_format *data)
{
	int			star[2];
	t_format	*save;

	star[0] = 0;
	star[1] = 0;
	save = data;
	if (msk(data, OPT_HSTAR))
	{
		get_arg_n(data, &star[0]);
		data = save;
		if (data->flag.width == 0)
		{
			if (star[0] < 0)
				data->flag.opts |= OPT_MINUS;
			data->flag.width = star[0] < 0 ? (star[0] * -1) : star[0];
		}
	}
	if (data->flag.star)
	{
		get_arg_n(data, &star[1]);
		data->flag.precision = star[1] < 0 ?
			data->flag.precision : (size_t)star[1];
		if (star[1] < 0)
			data->flag.opts &= ~OPT_PREC;
	}
}
