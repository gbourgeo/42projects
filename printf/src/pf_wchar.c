/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_wchar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 19:55:16 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/04/30 06:02:10 by gbourgeo         ###   ########.fr       */
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

static char		*wchar_to_char(int nb, char ptr[33])
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

static int		check_and_write(t_dt *data, wchar_t w, int len, int *size)
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
	wchar_to_char(w, ptr);
	i = 0;
	while (ptr[i])
	{
		write_char(data, ft_atouc(ptr + i));
		i += 8;
	}
	return (0);
}

void			write_wchar(t_dt *data, wchar_t *w, int *len)
{
	int			i;
	int			size;
	int			precision;

	i = 0;
	size = 0;
	precision = (data->flag.point && len[1] < len[0]) ? len[1] : len[0];
	while (i < precision)
	{
		if (w[i] > 127)
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
