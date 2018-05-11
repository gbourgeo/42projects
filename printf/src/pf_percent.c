/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_percent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 23:29:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/05/08 09:37:07 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			pf_percent(t_dt *data)
{
	if (!data->flag.minus)
	{
		while (data->flag.min_width > 1 && data->flag.min_width--)
			write_char(data, (data->flag.zero) ? '0' : ' ');
	}
	write_char(data, '%');
	if (data->flag.minus)
	{
		while (data->flag.min_width > 1 && data->flag.min_width--)
			write_char(data, ' ');
	}
}
