/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_x.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 04:14:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/04/11 02:23:46 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static ULL		get_modifier(t_dt *data, int *len)
{
	if (data->flag.len_modifier & ARG_Z && (*len = 16))
		return (va_arg(data->ap, unsigned long long));
	if (data->flag.len_modifier & ARG_J && (*len = 16))
		return (va_arg(data->ap, uintmax_t));
	if (data->flag.len_modifier & ARG_LL && (*len = 16))
		return (va_arg(data->ap, unsigned long long));
	if (data->flag.len_modifier & ARG_L && (*len = 16))
		return (va_arg(data->ap, unsigned long));
	if (data->flag.len_modifier & ARG_HH)
		return ((unsigned char)va_arg(data->ap, int));
	if (data->flag.len_modifier & ARG_H)
		return ((unsigned short)va_arg(data->ap, int));
	return (va_arg(data->ap, int));
}

static void		get_data(t_dt *data, t_av *av, int *len)
{
	av->ui = get_modifier(data, len);
	av->s = ft_itoa_base(av->ui, 16);
	av->len = ft_strlen(av->s);
	if (data->flag.point && av->ui == 0)
		av->len = 0;
	if (*data->tail == 'X')
		ft_strtoupper(av->s);
	if (data->flag.hash)
		data->flag.hash = 2;
	if (data->flag.hash && data->flag.zero && av->ui)
		write_str(data, (*data->tail == 'x') ? "0x" : "0X", 2);
}

static void		print_ox(t_dt *data, t_av *av)
{
	int			len;

	len = (data->flag.precision > av->len) ? data->flag.precision : av->len;
	if (!data->flag.minus)
	{
		while (data->flag.min_width > len + data->flag.hash &&
				data->flag.min_width--)
			write_char(data, (data->flag.zero) ? '0' : ' ');
	}
	if (data->flag.hash && !data->flag.zero && av->ui)
		write_str(data, (*data->tail == 'x') ? "0x" : "0X", 2);
	while (data->flag.precision > av->len &&
			data->flag.precision--)
		write_char(data, '0');
}

void			pf_x(t_dt *data)
{
	t_av		av;
	int			len;
	int			width;

	width = 8;
	get_data(data, &av, &width);
	print_ox(data, &av);
	len = ft_strlen((av.len >= width) ? &av.s[av.len - width] : av.s);
	if (av.len >= width)
		write_str(data, &av.s[av.len - width], len);
	else if (!data->flag.point || av.ui)
		write_str(data, av.s, len);
	if (data->flag.minus)
	{
		while (data->flag.min_width > av.len + data->flag.hash &&
				data->flag.min_width--)
			write_char(data, (data->flag.zero && !data->flag.hash) ? '0' : ' ');
	}
	if (av.s)
		free(av.s);
}
