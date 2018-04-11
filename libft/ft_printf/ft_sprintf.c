/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 02:56:04 by root              #+#    #+#             */
/*   Updated: 2018/04/11 03:31:17 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_sprintf.h"

int			ft_sprintf(char *str, const char *restrict format, ...)
{
	t_dt	data;
	int		ret;

	ft_memset(&data, 0, sizeof(data));
	*str = '\0';
	data.str = str;
	data.tail = (char *)format;
	data.writeto = ft_sprintf_write;
	va_start(data.ap, format);
	ret = pf_routine(&data);
	va_end(data.ap);
	return (ret);
}
