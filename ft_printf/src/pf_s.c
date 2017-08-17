/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_s.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 04:14:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/08/17 14:19:06 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int		*ft_wcharlen(const int *str, int *i)
{
	int			len;
	int			size;
	char		*ptr;

	len = 0;
	size = 0;
	if (str)
	{
		while (str[len])
		{
			if (str[len] > 127)
			{
				ptr = ft_itoa_base(str[len], 2);
				size += ft_strlen(ptr) / 6;
				free(ptr);
			}
			size++;
			len++;
		}
	}
	i[0] = len;
	i[1] = size;
	return (i);
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
		len[0] = data->flag.precision;
	if (!data->flag.minus)
	{
		while (data->flag.min_width > len[1] && data->flag.min_width--)
			write_char(data, (data->flag.zero) ? '0' : ' ');
	}
	write_wchar(data, s, len[1]);
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
