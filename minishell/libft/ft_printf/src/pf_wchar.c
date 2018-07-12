/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_wchar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 19:55:16 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/05/02 06:09:20 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_base_printf.h"

void			write_wstr(t_dt *data, wchar_t *s, size_t len)
{
	size_t		i;
	size_t		weight;

	i = 0;
	weight = 0;
	if (!s)
		return ;
	while (s[i] && weight < len)
	{
		weight += ft_wcharlen(s[i]);
		if (weight <= len)
			write_wchar(data, s[i]);
		i++;
	}
}

void			write_wchar(t_dt *data, wchar_t w)
{
	if (w <= 0x7F)
	{
		write_char(data, w);
	}
	else if (w <= 0x7FF)
	{
		write_char(data, (w >> 6) + 0xC0);
		write_char(data, (w & 0x3F) + 0x80);
	}
	else if (w <= 0xFFFF)
	{
		write_char(data, (w >> 12) + 0xE0);
		write_char(data, ((w >> 6) & 0x3F) + 0x80);
		write_char(data, (w & 0x3F) + 0x80);
	}
	else if (w <= 0x10FFFF)
	{
		write_char(data, (w >> 18) + 0xF0);
		write_char(data, ((w >> 12) & 0x3F) + 0x80);
		write_char(data, ((w >> 6) & 0x3F) + 0x80);
		write_char(data, (w & 0x3F) + 0x80);
	}
}
