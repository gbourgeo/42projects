/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 02:08:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/07/05 03:43:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

static size_t	ft_strlen(char *str)
{
	char		*ptr;

	ptr = str;
	while (*ptr)
		ptr++;
	return (ptr - str);
}

static char		*ft_itoa(int n)
{
	char		*p;
	int			sign;
	int			i;
	int			src;

	src = n;
	i = (n < 0 ? 3 : 2);
	while ((n /= 10))
		++i;
	if ((p = (char*)malloc(sizeof(*p) * i)) == NULL)
		return (NULL);
	p[--i] = '\0';
	if (src == 0)
		p[0] = '0';
	if ((sign = (src < 0 ? -1 : 1)) < 0)
		p[0] = '-';
	while (src != 0)
	{
		p[--i] = ((src % 10) * sign + 48);
		src /= 10;
	}
	return (p);
}

int				ft_printf(const char * restrict format, ...)
{
	t_dt		data;
	va_list		ap;
	char		*s;
	int			i;
	char		c;

	data.ret = 0;
	data.buff = (char *)format;
	va_start(ap, format);
	while (*data.buff)
	{
		if (*data.buff == CONV_CHAR)
		{
			data.buff++;

			if (*data.buff == 's')
			{
				s = va_arg(ap, char *);
				data.ret += write(STDOUT_FILENO, s, ft_strlen(s));
			}
			else if (*data.buff == 'd')
			{
				i = va_arg(ap, int);
				s = ft_itoa(i);
				data.ret += write(STDOUT_FILENO, s, ft_strlen(s));
				free(s);
			}
			if (*data.buff == 'c')
			{
				c = va_arg(ap, int);
				data.ret += write(STDOUT_FILENO, &c, 1);
			}

		}
		else
			data.ret += write(STDOUT_FILENO, data.buff, 1);
		data.buff++;
	}
	va_end(ap);
	return (data.ret);
}
