/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 09:53:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/05/08 10:29:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

static void	ft_asprintf_write(t_dt *data)
{
	int		len;
	void	*ptr;

	data->ret += data->pos;
	len = ft_strlen(data->stream);
	ptr = data->stream;
	if (data->pos == 0)
		return ;
	if ((data->stream = malloc(len + data->pos + 1)) == NULL)
	{
		if (ptr)
			free(ptr);
		exit(-1);
	}
	ft_memcpy(data->stream, ptr, len);
	ft_memcpy(data->stream + len, data->buff, data->pos);
	((char *)data->stream)[len + data->pos] = '\0';
}

int			ft_asprintf(char **ret, const char *format, ...)
{
	t_dt		data;

	ft_memset(&data, 0, sizeof(data));
	data.tail = (char *)format;
	va_start(data.ap, format);
	data.write_method = ft_asprintf_write;
	ft_base(&data);
	ft_asprintf_write(&data);
	va_end(data.ap);
	*ret = (char *)data.stream;
	return (data.ret - data.less);
}
