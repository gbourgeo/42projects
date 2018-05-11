/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 09:47:17 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/05/08 10:37:35 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static void	ft_snprintf_write(t_dt *data)
{
	int		writes;

	writes = (data->stream_size > data->pos) ? data->pos : data->stream_size;
	data->ret += data->pos;
	if (data->stream_size == 0)
		return ;
	ft_memcpy((char *)data->stream, data->buff, writes);
	data->stream_size = writes;
}

int			ft_snprintf(char *restrict str, size_t size, const char *restrict format, ...)
{
	t_dt	data;

	ft_memset(&data, 0, sizeof(data));
	if (size == 0)
		return (0);
	data.tail = (char *)format;
	va_start(data.ap, format);
	data.write_method = ft_snprintf_write;
	data.stream = str;
	data.stream_size = size - 1;
	ft_base(&data);
	ft_snprintf_write(&data);
	((char *)(data.stream))[size] = '\0';
	va_end(data.ap);
	return (data.ret - data.less);
}
