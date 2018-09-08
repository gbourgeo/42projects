/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_di.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 04:22:17 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/04/11 02:23:39 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static ULL	get_modifier(t_dt *data)
{
	if (*data->tail == 'D')
		return (va_arg(data->ap, unsigned long long));
	if (data->flag.len_modifier & ARG_Z)
		return (va_arg(data->ap, size_t));
	if (data->flag.len_modifier & ARG_J)
		return (va_arg(data->ap, intmax_t));
	if (data->flag.len_modifier & ARG_LL)
		return (va_arg(data->ap, long long));
	if (data->flag.len_modifier & ARG_L)
		return (va_arg(data->ap, long));
	if (data->flag.len_modifier & ARG_HH)
		return ((signed char)va_arg(data->ap, int));
	if (data->flag.len_modifier & ARG_H)
		return ((short)va_arg(data->ap, int));
	return (va_arg(data->ap, int));
}

static void	pf_di_c(t_dt *data, t_av *av, char c)
{
	int		len;

	len = (data->flag.precision > av->len) ? data->flag.precision : av->len;
	len++;
	if (!data->flag.minus && data->flag.zero)
		write_char(data, c);
	if (!data->flag.minus)
	{
		while (data->flag.min_width > len && data->flag.min_width--)
			write_char(data,
						(data->flag.zero && !data->flag.point) ? '0' : ' ');
	}
	if (data->flag.minus || !data->flag.zero)
		write_char(data, c);
	while (len - 1 > av->len && len--)
		write_char(data, '0');
	write_str(data, av->s, av->len);
	if (data->flag.minus)
	{
		len = (data->flag.precision > av->len) ? data->flag.precision : av->len;
		len++;
		while (data->flag.min_width > len && data->flag.min_width--)
			write_char(data, ' ');
	}
}

static void	pf_di_noc(t_dt *data, t_av *av)
{
	int		len;

	len = (data->flag.precision > av->len) ? data->flag.precision : av->len;
	if (!data->flag.minus)
	{
		while (data->flag.min_width > len && data->flag.min_width--)
			write_char(data,
						(data->flag.zero && !data->flag.point) ? '0' : ' ');
	}
	while (len > av->len && len--)
		write_char(data, '0');
	if (!data->flag.point ||
		(data->flag.point && (data->flag.precision > 0 || av->ui != 0)))
		write_str(data, av->s, av->len);
	else if (data->flag.min_width)
		write_char(data, ' ');
	if (data->flag.minus)
	{
		len = (data->flag.precision > av->len) ? data->flag.precision : av->len;
		while (data->flag.min_width > len && data->flag.min_width--)
			write_char(data, ' ');
	}
}

void		pf_di(t_dt *data)
{
	t_av	av;
	char	c;

	av.ui = get_modifier(data);
	av.s = ft_itoa_base(((LL)av.ui < 0) ? av.ui * -1 : av.ui, 10);
	av.len = ft_strlen(av.s);
	c = '\0';
	if ((LL)av.ui < 0)
		c = '-';
	else if (data->flag.plus)
		c = '+';
	else if (data->flag.space)
		c = ' ';
	if (c)
		pf_di_c(data, &av, c);
	else
		pf_di_noc(data, &av);
	if (av.s)
		free(av.s);
}
