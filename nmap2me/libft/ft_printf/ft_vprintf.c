/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 13:05:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/07/17 13:18:50 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "ft_vprintf.h"

int				ft_vprintf(const char *format, va_list ap)
{
	t_dt		data;
	int			ret;

	ft_memset(&data, 0, sizeof(data));
	data.fd = STDOUT_FILENO;
	data.tail = (char *)format;
	data.writeto = ft_vprintf_write;
	va_copy(data.ap, ap);
	ret = pf_routine(&data);
	va_end(data.ap);
	return (ret);
}
