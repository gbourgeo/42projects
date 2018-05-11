/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 10:30:21 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/05/08 10:33:51 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void	ft_dprintf_write(t_dt *data)
{
	data->ret += data->pos;
	write(*(int *)data->stream, data->buff, data->pos);
}

int			ft_dprintf(int fd, const char *restrict format, ...)
{
	t_dt		data;

	ft_memset(&data, 0, sizeof(data));
	data.tail = (char *)format;
	va_start(data.ap, format);
	data.write_method = ft_dprintf_write;
	data.stream = &fd;
	ft_base(&data);
	ft_dprintf_write(&data);
	va_end(data.ap);
	return (data.ret - data.less);
}
