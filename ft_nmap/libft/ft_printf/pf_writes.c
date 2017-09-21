/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_writes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 22:27:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/09/21 01:46:02 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <unistd.h>

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
