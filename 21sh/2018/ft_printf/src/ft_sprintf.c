/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/21 07:19:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/21 07:19:33 by gbourgeo         ###   ########.fr       */
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
