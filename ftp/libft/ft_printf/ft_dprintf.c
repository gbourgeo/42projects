/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 07:17:15 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/21 07:17:15 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_dprintf.h"

int			ft_dprintf(int fd, const char *restrict format, ...)
{
	t_dt	data;
	int		ret;

	ft_memset(&data, 0, sizeof(data));
	data.fd = fd;
	data.tail = (char *)format;
	data.writeto = ft_dprintf_write;
	va_start(data.ap, format);
	ret = pf_routine(&data);
	va_end(data.ap);
	return (ret);
}
