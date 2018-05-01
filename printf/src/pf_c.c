/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_c.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 04:14:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/05/01 01:20:30 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static void		fill_buff(char ret[33], int *i, int size)
{
	int			len;
	int			mod;

	ft_bzero(ret, 33);
	*i = 0;
	len = size / 6 + 1;
	mod = 8 - size % 6 - len - 1;
	while (*i < len)
		ret[(*i)++] = '1';
	ret[(*i)++] = '0';
	while (mod-- > 0)
		ret[(*i)++] = '0';
}

static char		*wchar_to_char(wint_t nb, char ptr[33])
{
	char		bin[28];
	int			i;
	int			j;

	ft_itoa_base2(nb, 2, bin);
	fill_buff(ptr, &i, ft_strlen(bin));
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

static int		check_and_write(t_dt *data, wint_t w, wint_t len, int *size)
{
	char		ptr[33];
	wint_t		x;
	int			i;

	x = w;
	if (data->flag.point)
	{
		while ((x = x >> 6))
			(*size)++;
		if (*size >= len)
			return (1);
	}
	wchar_to_char(w, ptr);
	i = 0;
	while (ptr[i])
	{
		write_char(data, ft_atouc(ptr + i));
		i += 8;
	}
	return (0);
}

static void		write_wint(t_dt *data, wint_t *w, wint_t *len)
{
	int			i;
	int			size;
	int			precision;

	i = 0;
	size = 0;
	precision = (data->flag.point && len[1] < len[0]) ? len[1] : len[0];
	while (i < precision)
	{
		if (w[i] > 0x7F)
		{
			if (check_and_write(data, w[i], len[1], &size))
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
	wint_t	ui[2];
	int		len;
	int		width;

	ui[0] = 1;
	ui[1] = va_arg(data->ap, wint_t);
	len = 4;
	width = 1;
	if (ui[1] <= 0x7F)
	{len = 1;width = 0;}
	else if (ui[1] <= 0x7FF)
	{len = 2;width = 0;}
	else if (ui[1] <= 0xFFF)
	{len = 3;width = 0;}
	if (!data->flag.minus)
	{
		while (data->flag.min_width > len - width  && data->flag.min_width--)
			write_char(data, (data->flag.zero) ? '0' : ' ');
	}
	if ((*data->tail == 'C' || data->flag.len_modifier) && ui[1] > 0x7F)
		write_wint(data, &ui[1], ui);
	else
		write_char(data, ui[1]);
	if (data->flag.minus)
	{
		while (data->flag.min_width > len - width && data->flag.min_width--)
			write_char(data, ' ');
	}
}
