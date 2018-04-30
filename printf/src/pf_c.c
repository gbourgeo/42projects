/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_c.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 04:14:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/04/30 06:42:15 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int		fill_buff(char *ret, int size)
{
	int			len;
	int			mod;
	int			i;

	ft_bzero(ret, 33);
	i = 0;
	len = size / 6 + 1;
	mod = 8 - size % 6 - len - 1;
	while (i < len)
		ret[i++] = '1';
	ret[i++] = '0';
	while (mod-- > 0)
		ret[i++] = '0';
	return (i);
}

static char		*wint_to_char(int nb, char *ptr)
{
	char		bin[28];
	int			i;
	int			j;

	ft_itoa_base2(nb, 2, bin);
	i = fill_buff(ptr, ft_strlen(bin));
	j = 0;
	while (bin[j])
	{
		if (i % 8 == 0)
		{
			ptr[i++] = '1';
			ptr[i++] = '0';
		}
		ptr[i++] = bin[j];
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static int		get_length(unsigned char w)
{
	char		ptr[33];

	wint_to_char(w, ptr);
	return (ft_strlen(ptr) / 8);
}

static int	get_uchar_length(t_dt *data, int ui[2])
{
	int			i;
	int			size;
	int			precision;
	wint_t		*w;
	int			len;

	i = 0;
	size = 0;
	precision = (data->flag.point && ui[1] < ui[0]) ? ui[1] : ui[0];
	w = &ui[1];
	len = 0;
	while (i < precision)
	{
		if (w[i] > 127)
			len += get_length(w[i]);
		else
			len++;
		size++;
		i++;
	}
	return (len);
}

static int		check_and_write(t_dt *data, wint_t w, int len, int *size)
{
	char		ptr[33];
	wchar_t		x;
	int			i;

	x = w;
	if (data->flag.point)
	{
		while ((x = x >> 6))
			(*size)++;
		if (*size >= len)
			return (1);
	}
	wint_to_char(w, ptr);
	i = 0;
	while (ptr[i])
	{
		write_char(data, ft_atouc(ptr + i));
		i += 8;
	}
	return (0);
}

static void	write_wint(t_dt *data, int ui[2])
{
	int			i;
	int			size;
	int			precision;
	wint_t		*w;

	i = 0;
	size = 0;
	precision = (data->flag.point && ui[1] < ui[0]) ? ui[1] : ui[0];
	w = (wint_t *)&ui[1];
	while (i < precision)
	{
		if (w[i] > 127)
		{
			if (check_and_write(data, w[i], ui[1], &size))
				return ;
		}
		else
			write_char(data, w[i]);
		size++;
		i++;
	}
}

void		pf_c(t_dt *data)
{
	int		ui[2];
	int		len;

	ui[0] = 1;
	ui[1] = va_arg(data->ap, int);
	len = get_uchar_length(data, ui);
	if (!data->flag.minus)
	{
		while (data->flag.min_width > len && data->flag.min_width--)
			write_char(data, (data->flag.zero) ? '0' : ' ');
	}
	if ((*data->tail == 'C' || data->flag.len_modifier))
		write_wint(data, ui);
	else
		write_char(data, ui[1]);
	if (data->flag.minus)
	{
		while (data->flag.min_width > len + 1 && data->flag.min_width--)
			write_char(data, ' ');
	}
}
