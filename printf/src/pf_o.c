/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_o.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 04:14:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/05/08 09:36:44 by gbourgeo         ###   ########.fr       */
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

static void	no_minus(t_dt *data, t_av *av)
{
	size_t	width;
	size_t	print_zero;

	width = av->len;
	if (data->flag.hash && av->ui)
		width += 1;
	if (data->flag.precision > width)
		width = data->flag.precision;
	print_zero = data->flag.zero && !data->flag.precision;
	while (data->flag.min_width > width && data->flag.min_width--)
		write_char(data, (print_zero) ? '0' : ' ');
}

static void	minus(t_dt *data, t_av *av)
{
	size_t	width;

	width = av->len;
	if (data->flag.hash && av->ui)
		width += 1;
	if (data->flag.precision > width)
		width = data->flag.precision;
	while (data->flag.min_width > width && data->flag.min_width--)
		write_char(data, ' ');
}

void		pf_o(t_dt *data)
{
	t_av	av;
	size_t	width;
	size_t	precision;

	av.ui = get_modifier(data);
	ft_itoa_base2(av.ui, 8, av.s);
	av.len = ft_strlen(av.s);
	if (!data->flag.minus)
		no_minus(data, &av);
	if (data->flag.hash && av.ui)
		write_char(data, '0');
	precision = data->flag.precision;
	width = (data->flag.hash && av.ui) ? av.len + 1 : av.len;
	while (precision > width && precision--)
		write_char(data, '0');
	write_str(data, av.s, av.len);
	if (data->flag.minus)
		minus(data, &av);
}
