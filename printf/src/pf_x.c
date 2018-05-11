/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_x.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 04:14:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/05/08 09:37:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static ULL		get_modifier(t_dt *data, size_t *len)
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

static void		get_data(t_dt *data, t_av *av, size_t *len, char **ptr)
{
	av->ui = get_modifier(data, len);
	ft_itoa_base2(av->ui, 16, av->s);
	av->len = ft_strlen(av->s);
	*ptr = (av->len >= *len) ? &av->s[av->len - *len] : av->s;
	av->len = ft_strlen(*ptr);
	if (data->flag.point && av->ui == 0)
		av->len = 1;
	if (*data->tail == 'X')
		ft_strtoupper(*ptr);
}

static void		print_ox(t_dt *data, t_av *av)
{
	size_t		len;
	int			print;
	size_t		precision;

	len = (data->flag.precision > av->len) ? data->flag.precision : av->len;
	if (data->flag.hash && av->ui)
		len += 2;
	print = data->flag.zero && !data->flag.precision;
	if (data->flag.hash && av->ui && data->flag.zero && print)
		write_str(data, (*data->tail == 'x') ? "0x" : "0X", 2);
	if (!data->flag.minus)
	{
		while (data->flag.min_width > len && data->flag.min_width--)
			write_char(data, (print) ? '0' : ' ');
	}
	if (data->flag.hash && av->ui && !print)
		write_str(data, (*data->tail == 'x') ? "0x" : "0X", 2);
	precision = data->flag.precision;
	while (precision > av->len && precision--)
		write_char(data, '0');
}

void			pf_x(t_dt *data)
{
	t_av		av;
	char		*ptr;
	size_t		len;
	size_t		width;

	width = 8;
	get_data(data, &av, &width, &ptr);
	print_ox(data, &av);
	write_str(data, ptr, ft_strlen(ptr));
	if (data->flag.minus)
	{
		len = (data->flag.precision > av.len) ? data->flag.precision : av.len;
		if (data->flag.hash && av.ui)
			len += 2;
		while (data->flag.min_width > len && data->flag.min_width--)
			write_char(data, (data->flag.zero && !data->flag.hash) ? '0' : ' ');
	}
}
