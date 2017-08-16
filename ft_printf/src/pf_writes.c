/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_writes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 22:27:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/08/16 04:11:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

void		write_str(t_dt *data, const void *str)
{
	if (!str)
		return ;
	while (*(char *)str)
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

void		write_char(t_dt *data, char c)
{
	data->buff[data->pos++] = c;
	if (data->pos >= PRINTF_BUFF)
	{
		data->ret += PRINTF_BUFF;
		write(STDOUT_FILENO, data->buff, data->pos);
		data->pos = 0;
	}
}
