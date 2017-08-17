/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_c.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 04:14:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/08/17 11:21:50 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		pf_c(t_dt *data)
{
	int		ui;

	ui = va_arg(data->ap, int);
	if (!data->flag.minus)
	{
		while (data->flag.min_width > 1 && data->flag.min_width--)
			write_char(data, (data->flag.zero) ? '0' : ' ');
	}
	if (ui > 127)
		write_wchar(data, &ui, 1);
	else
		write_char(data, ui);
	if (data->flag.minus)
	{
		while (data->flag.min_width > 1 && data->flag.min_width--)
			write_char(data, ' ');
	}
}
