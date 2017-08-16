/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_s.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 04:14:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/08/16 14:43:22 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <unistd.h>

static char		*wchar_to_char(wchar_t *str)
{
	char		*bin;
	char		ret[33];
	int			i;
	int			j;
	int			len;
	int			mod;

	while (*str)
	{
		bin = ft_itoa_base(*str, 2);
		ft_bzero(ret, 33);
		i = 0;
		j = 0;
		len = ft_strlen(bin) / 6 + 1;
		mod = 8 - ft_strlen(bin) % 6 - len - 1;
		while (i < len)
			ret[i++] = '1';
		ret[i++] = '0';
		while (mod--)
			ret[i++] = '0';
		while (bin[j])
		{
			if (i % 8 == 0)
			{
				write(1, &ret[i - 8], 8); write(1, " ", 1);
				ret[i++] = '1';
				ret[i++] = '0';
			}
			ret[i++] = bin[j];
			j++;
		}
		ret[i] = '\0';
		write(1, &ret[i - 8], 8); write(1, " ", 1);
		return (ft_strdup(ret));
		str++;
	}
	return (ft_strdup(ret));
}

static int		ft_atoc(char *str)
{
	int			i;
	int			c;

	i = 8;
	c = 0;
	while (i-- >= 0)
	{
		if (str[i] == '1')
			c |= 1;
		else
			c |= 0;
		c = c << 1;
	}
	ft_putnbr(c);write(1, " ", 1);
	return (c);
}

static void		pf_big_s(t_dt *data)
{
	wchar_t		*str;
	char		*ptr;
	int			i;
	

	str = va_arg(data->ap, wchar_t *);
	if (str == NULL)
		str = L"(null)";
	ptr = wchar_to_char(str);
	i = 0;
	while (ptr[i])
	{
		write_char(data, ft_atoc(ptr + i));
		i += 8;
	}
	free(ptr);
}

static void		pf_small_s(t_dt *data)
{
	t_av		av;

	av.s = ft_strdup(va_arg(data->ap, char *));
	if (av.s == NULL)
		av.s = ft_strdup("(null)");
	av.len = ft_strlen(av.s);
	if (data->flag.point && data->flag.precision < av.len)
		av.len = data->flag.precision;
	av.s[av.len] = '\0';
	if (!data->flag.minus)
	{
		while (data->flag.min_width > av.len && data->flag.min_width--)
			write_char(data, (data->flag.zero) ? '0' : ' ');
	}
	write_str(data, av.s);
	if (data->flag.minus)
	{
		while (data->flag.min_width > av.len && data->flag.min_width--)
			write_char(data, ' ');
	}
	if (av.s)
		free(av.s);
}

void			pf_s(t_dt *data)
{
	if (*data->tail == 'S' || data->flag.len_modifier & ARG_L)
		pf_big_s(data);
	else
		pf_small_s(data);
}
