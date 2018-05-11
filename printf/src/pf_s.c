/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_s.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 04:14:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/05/08 09:37:50 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int		get_precision_2(size_t *ret, const wchar_t *w, const size_t max)
{
	if (*w <= 0x7FF)
	{
		if (*ret + 2 > max)
			return (1);
		*ret = *ret + 2;
	}
	else if (*w <= 0xFFFF)
	{
		if (*ret + 3 > max)
			return (1);
		*ret += 3;
	}
	else if (*w <= 0x10FFFF)
	{
		if (*ret + 4 > max)
			return (1);
		*ret += 4;
	}
	return (0);
}

static size_t	get_precision(const wchar_t *str, const size_t max)
{
	size_t		i;
	size_t		ret;

	i = 0;
	ret = 0;
	if (!str)
		return (0);
	while (str && str[i])
	{
		if (str[i] <= 0x7F)
		{
			if (ret + 1 > max)
				return (ret);
			ret++;
		}
		else if (get_precision_2(&ret, &str[i], max))
			return (ret);
		i++;
	}
	return (ret);
}

static void		pf_big_s(t_dt *data)
{
	wchar_t		*s;
	size_t		len;

	s = va_arg(data->ap, wchar_t *);
	if (s == NULL)
		s = L"(null)";
	len = ft_wstrlen(s);
	if (data->flag.point && data->flag.precision < len)
		len = get_precision(s, data->flag.precision);
	if (!data->flag.minus)
	{
		while (data->flag.min_width > len && data->flag.min_width--)
			write_char(data, (data->flag.zero) ? '0' : ' ');
	}
	write_wstr(data, s, len);
	if (data->flag.minus)
	{
		while (data->flag.min_width > len && data->flag.min_width--)
			write_char(data, ' ');
	}
}

static void		pf_small_s(t_dt *data)
{
	t_av		av;

	av.str = va_arg(data->ap, char *);
	if (av.str == NULL)
		av.str = "(null)";
	av.len = ft_strlen(av.str);
	if (data->flag.point && data->flag.precision < av.len)
		av.len = data->flag.precision;
	if (!data->flag.minus)
	{
		while (data->flag.min_width > av.len && data->flag.min_width--)
			write_char(data, (data->flag.zero) ? '0' : ' ');
	}
	write_str(data, av.str, av.len);
	if (data->flag.minus)
	{
		while (data->flag.min_width > av.len && data->flag.min_width--)
			write_char(data, ' ');
	}
}

void			pf_s(t_dt *data)
{
	if (*data->tail == 'S' || data->flag.len_modifier & ARG_L)
		pf_big_s(data);
	else
		pf_small_s(data);
}
