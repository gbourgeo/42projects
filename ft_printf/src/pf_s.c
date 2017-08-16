/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_s.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 04:14:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/08/16 04:58:55 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <unistd.h>

static void		write_wstr_t(t_dt *data, wchar_t *str)
{
	if (!str)
		return ;
	while (*str)
	{
		data->buff[data->pos++] = *(char *)str;
		if (data->pos >= PRINTF_BUFF)
		{
			data->ret += PRINTF_BUFF;
			write(STDOUT_FILENO, data->buff, data->pos);
			data->pos = 0;
		}
		str++;
	}
}

static wchar_t	*pf_strdup(wchar_t *s)
{
	wchar_t		*ret;
	size_t		i;

	ret = NULL;
	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
		i++;
	if ((ret = malloc((i + 1) * sizeof(wchar_t))) == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ft_memcpy(&ret[i], &s[i], sizeof(wchar_t));
		i++;
	}
	ret[i] = L'\0';
	return (ret);
}

static void		pf_big_s(t_dt *data)
{
	wchar_t		*str;
	int			len;

	str = pf_strdup(va_arg(data->ap, wchar_t *));
	if (str == NULL)
		str = pf_strdup(L"(null)");
	len = 0;
	while (str[len])
		len++;
	if (data->flag.point && data->flag.precision < len)
		len = data->flag.precision;
	str[len] = L'\0';
	if (!data->flag.minus)
	{
		while (data->flag.min_width > len && data->flag.min_width--)
			write_char(data, (data->flag.zero) ? '0' : ' ');
	}
	write_wstr_t(data, str);
	if (data->flag.minus)
	{
		while (data->flag.min_width > len && data->flag.min_width--)
			write_char(data, ' ');
	}
	if (str)
		free(str);
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
