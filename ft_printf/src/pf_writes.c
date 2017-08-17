/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_writes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 22:27:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/08/17 19:39:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static void		fill_buff(char *ret, int *i, int size)
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
	while (mod--)
		ret[(*i)++] = '0';
}

static char		*wchar_to_char(int nb)
{
	char		*bin;
	char		ret[33];
	int			i;
	int			j;

	bin = ft_itoa_base(nb, 2);
	fill_buff(ret, &i, ft_strlen(bin));
	j = 0;
	while (bin[j])
	{
		if (i % 8 == 0)
		{
			ret[i++] = '1';
			ret[i++] = '0';
		}
		ret[i++] = bin[j];
		j++;
	}
	ret[i] = '\0';
	free(bin);
	return (ft_strdup(ret));
}

void			write_wchar(t_dt *data, wchar_t *w, int *len)
{
	char		*ptr;
	int			i;
	int			j;
	int			size;

	j = 0;
	size = 0;
	while (j < len[0])
	{
		if (w[j] > 127)
		{
			ptr = wchar_to_char(w[j]);
			if (data->flag.point)
			{
				int x = w[j];
				while ((x = x >> 6))
					size++;
				if (size >= len[1])
					return (free(ptr));
			}
			i = 0;
			while (ptr[i])
			{
				write_char(data, ft_atouc(ptr + i));
				i += 8;
			}
			free(ptr);
			ptr = NULL;
		}
		else
			write_char(data, w[j]);
		size++;
		j++;
	}
}

void			write_str(t_dt *data, const char *str, int len)
{
	int			j;

	j = 0;
	if (!str)
		return ;
	while (j < len)
	{
		data->buff[data->pos++] = str[j];
		if (data->pos >= PRINTF_BUFF)
		{
			data->ret += PRINTF_BUFF;
			write(STDOUT_FILENO, data->buff, data->pos);
			data->pos = 0;
		}
		j++;
	}
}

void			write_char(t_dt *data, unsigned char c)
{
	data->buff[data->pos++] = c;
	if (data->pos >= PRINTF_BUFF)
	{
		data->ret += PRINTF_BUFF;
		write(STDOUT_FILENO, data->buff, data->pos);
		data->pos = 0;
	}
}
