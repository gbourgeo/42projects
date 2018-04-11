/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_o.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 04:14:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/04/11 02:23:36 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static ULL	get_modifier(t_dt *data)
{
	if (*data->tail == 'O')
		return (va_arg(data->ap, unsigned long long));
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

static void	print_zero_space(t_dt *data, t_av *av)
{
	int		len;

	len = (data->flag.precision > av->len) ? data->flag.precision : av->len;
	if (!av->ui)
		len = 0;
	if (!data->flag.minus)
	{
		while (data->flag.min_width > len && data->flag.min_width--)
			write_char(data, (data->flag.zero) ? '0' : ' ');
	}
	while (data->flag.precision > av->len && data->flag.precision--)
		write_char(data, '0');
	if (data->flag.hash && av->ui)
		write_char(data, '0');
}

void		pf_o(t_dt *data)
{
	t_av	av;
	int		len;

	av.ui = get_modifier(data);
	av.s = ft_itoa_base(av.ui, 8);
	av.len = ft_strlen(av.s) + data->flag.hash;
	len = (data->flag.precision > av.len) ? data->flag.precision : av.len;
	print_zero_space(data, &av);
	if (*data->tail == 'o')
	{
		if (data->flag.hash || !data->flag.point || av.ui)
			write_str(data, av.s, av.len - data->flag.hash);
	}
	else if (!data->flag.point || *(data->flag.point + 1) != '0')
		write_str(data, av.s, av.len - data->flag.hash);
	if (data->flag.minus)
	{
		while (data->flag.min_width > len && data->flag.min_width--)
			write_char(data, ' ');
	}
	if (av.s)
		free(av.s);
}
