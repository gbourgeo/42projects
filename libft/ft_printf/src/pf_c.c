/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_c.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 04:14:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/05/02 06:06:32 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_base_printf.h"

void		pf_c(t_dt *data)
{
	wint_t	ui;
	size_t	len;

	ui = va_arg(data->ap, wint_t);
	len = ft_wcharlen(ui);
	if (!data->flag.minus)
	{
		while (data->flag.min_width > len && data->flag.min_width--)
			write_char(data, (data->flag.zero) ? '0' : ' ');
	}
	if ((*data->tail == 'C' || data->flag.len_modifier) && len > 1)
		write_wchar(data, ui);
	else
		write_char(data, ui);
	if (data->flag.minus)
	{
		while (data->flag.min_width > len && data->flag.min_width--)
			write_char(data, ' ');
	}
}
