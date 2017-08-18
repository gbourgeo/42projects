/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_s.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 04:14:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/08/18 08:16:00 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

/*
** In pf_big_s(), the 'int len[2]'  to:
** len[0] = the number of ints in *str.
** len[1] = The number of characters to write to print each ints.
*/

static int		*ft_wcharlen(const int *str, int *i)
{
	int			w;

	i[0] = 0;
	i[1] = 0;
	w = 0;
	if (str)
	{
		while (str[i[0]])
		{
			if (str[i[0]] > 127)
			{
				w = str[i[0]];
				while ((w = w >> 6))
					i[1]++;
			}
			i[1]++;
			i[0]++;
		}
	}
	return (i);
}

static void		find_precision(t_dt *data, const int *str, int *len)
{
	int			i;
	int			w;
	int			precision;

	i = 0;
	precision = 0;
	if (!str)
		return ;
	len[1] = 0;
	while (*str && len[1] < data->flag.precision)
	{
		if (*str > 127)
		{
			w = *str;
			while ((w = w >> 6))
				precision++;
			if (len[1] + precision > data->flag.precision)
				return ;
			len[1] += precision;
		}
		len[1]++;
		str++;
	}
}

static void		pf_big_s(t_dt *data)
{
	wchar_t		*s;
	int			len[2];

	s = va_arg(data->ap, wchar_t *);
	if (s == NULL)
		s = L"(null)";
	ft_wcharlen(s, len);
	if (data->flag.point && data->flag.precision < len[1])
		find_precision(data, s, len);
	if (!data->flag.minus)
	{
		while (data->flag.min_width > len[1] && data->flag.min_width--)
			write_char(data, (data->flag.zero) ? '0' : ' ');
	}
	write_wchar(data, s, len);
	if (data->flag.minus)
	{
		while (data->flag.min_width > len[1] && data->flag.min_width--)
			write_char(data, ' ');
	}
}

static void		pf_small_s(t_dt *data)
{
	t_av		av;

	av.s = va_arg(data->ap, char *);
	if (av.s == NULL)
		av.s = "(null)";
	av.len = ft_strlen(av.s);
	if (data->flag.point && data->flag.precision < av.len)
		av.len = data->flag.precision;
	if (!data->flag.minus)
	{
		while (data->flag.min_width > av.len && data->flag.min_width--)
			write_char(data, (data->flag.zero) ? '0' : ' ');
	}
	write_str(data, av.s, av.len);
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
