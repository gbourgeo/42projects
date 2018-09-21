/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 07:18:19 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/21 07:18:58 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_snprintf.h"

int			ft_snprintf(char *str, size_t size,
						const char *restrict format, ...)
{
	t_dt	data;
	int		ret;

	ft_memset(&data, 0, sizeof(data));
	*str = '\0';
	data.str = str;
	data.str_size = size;
	data.tail = (char *)format;
	data.writeto = ft_snprintf_write;
	va_start(data.ap, format);
	ret = pf_routine(&data);
	va_end(data.ap);
	return (ret);
}
