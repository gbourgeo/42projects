/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_writes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 22:27:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/05/08 10:15:55 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			write_str(t_dt *data, const char *str, size_t len)
{
	size_t		j;

	j = 0;
	if (!str)
		return ;
	while (j < len)
		write_char(data, str[j++]);
}

void			write_char(t_dt *data, unsigned char c)
{
	data->buff[data->pos++] = c;
	if (data->pos >= PRINTF_BUFF)
	{
		data->write_method(data);
		data->pos = 0;
	}
}
