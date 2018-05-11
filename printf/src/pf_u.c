/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_u.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 04:14:39 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/05/08 09:37:33 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static ULL	get_modifier(t_dt *data)
{
	if (*data->tail == 'U')
		return (va_arg(data->ap, unsigned long));
	if (data->flag.len_modifier & ARG_Z)
		return (va_arg(data->ap, size_t));
	if (data->flag.len_modifier & ARG_J)
		return (va_arg(data->ap, uintmax_t));
	if (data->flag.len_modifier & ARG_LL)
		return (va_arg(data->ap, unsigned long long));
	if (data->flag.len_modifier & ARG_L)
		return (va_arg(data->ap, unsigned long));
	if (data->flag.len_modifier & ARG_HH)
		return ((unsigned char)va_arg(data->ap, int));
	if (data->flag.len_modifier & ARG_H)
		return ((unsigned short)va_arg(data->ap, int));
	return (va_arg(data->ap, unsigned int));
}

void		pf_u(t_dt *data)
{
	t_av	av;
	size_t	len;

	av.ui = get_modifier(data);
	ft_itoa_base2(av.ui, 10, av.s);
	av.len = ft_strlen(av.s);
	len = (data->flag.precision > av.len) ? data->flag.precision : av.len;
	if (!data->flag.minus)
	{
		while (data->flag.min_width > len && data->flag.min_width--)
			write_char(data, (data->flag.zero && !data->flag.precision) ?
						'0' : ' ');
	}
	if (data->flag.hash)
		write_char(data, '0');
	while (data->flag.precision > av.len && data->flag.precision--)
		write_char(data, '0');
	write_str(data, av.s, av.len);
	if (data->flag.minus && data->flag.min_width > data->flag.precision)
	{
		while (data->flag.min_width > len && data->flag.min_width--)
			write_char(data, ' ');
	}
}
