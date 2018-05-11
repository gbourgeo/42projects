/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 08:50:05 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/05/08 10:16:44 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static void	ft_fprintf_write(t_dt *data)
{
	data->ret += data->pos;
	fwrite(data->buff, sizeof(*data->buff), data->pos, (FILE *)data->stream);
}

int			ft_fprintf(FILE *restrict stream, const char *restrict format, ...)
{
	t_dt	data;

	ft_memset(&data, 0, sizeof(data));
	va_start(data.ap, format);
	data.tail = (char *)format;
	data.stream = stream;
	data.write_method = ft_fprintf_write;
	ft_base(&data);
	ft_fprintf_write(&data);
	va_end(data.ap);
	return (data.ret - data.less);
}
