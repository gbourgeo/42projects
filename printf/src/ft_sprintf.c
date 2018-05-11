/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 09:27:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/05/08 10:17:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static void	ft_sprintf_write(t_dt *data)
{
	data->ret += data->pos;
	ft_memcpy((char *)data->stream, data->buff, data->pos);
}

int			ft_sprintf(char *restrict str, const char *restrict format, ...)
{
	t_dt		data;

	ft_memset(&data, 0, sizeof(data));
	data.tail = (char *)format;
	va_start(data.ap, format);
	data.write_method = ft_sprintf_write;
	data.stream = str;
	ft_base(&data);
	ft_sprintf_write(&data);
	va_end(data.ap);
	return (data.ret - data.less);
}
