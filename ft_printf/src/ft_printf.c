/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 02:08:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/08/09 21:21:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <unistd.h>

#include <stdio.h>

static int		ft_atos(t_dt *data)
{
	int			ret;
	char		*ptr;

	ret = 0;
	ptr = data->tail;
	while (*ptr && ((*ptr >= '0' && *ptr <= '9') || *ptr == '+'))
		ptr++;
	while (data->tail < ptr)
	{
		if (*data->tail >= '0' && *data->tail <= '9')
		{
			if (data->tail + 1 != ptr)
				ret += ((ptr - data->tail - 1) * 10 * (*data->tail - '0'));
			else
				ret += (*data->tail - '0');
		}
		data->tail++;
	}
	return (ret);
}

static char		*ft_itohex(int nb)
{
	char		*ret;
	char		*base;
	int			size;
	int			i;

	ret = NULL;
	base = "0123456789abcdef";
	size = 0;
	i = nb;
	while (i)
	{
		i /= 16;
		size++;
	}
	ret = (nb == 0) ? ft_strnew(2) : ft_strnew(size + 1);
	ret[0] = '0';
	i = nb;
	while (i)
	{
		if (i < 0)
			ret[size - 1] = base[size - i % 16];
		else
			ret[size - 1] = base[i % 16];
		size--;
		i /= 16;
	}
	return (ret);
}

static void		get_padding(t_dt *data)
{
	int			neg;

	neg = 1;
	if (*data->tail == '-')
	{
		neg = -1;
		data->tail++;
	}
	data->last->pad_left = ft_atos(data) * neg;
	if (*data->tail == '.')
	{
		data->tail++;
		data->last->pad_right = ft_atos(data);
	}
//	printf("%d %d\n", data->pad_left, data->pad_right);
}

static void		get_args_x(t_dt *data, va_list *ap)
{
	data->last->type = ARG_X;
	data->last->ui = va_arg(*ap, int);
	data->last->next = NULL;
	data->last->s = ft_itohex(data->last->ui);
	data->last->len = ft_strlen(data->last->s);
}

static t_args	*new_arg(t_dt *data)
{
	t_args		*ptr;

	if ((ptr = malloc(sizeof(*ptr))) == NULL)
		return (NULL);
	ft_memset(ptr, 0, sizeof(*ptr));
	data->last = ptr;
	if (data->args == NULL)
		data->args = ptr;
	return (ptr);
}

int				ft_printf(const char * restrict format, ...)
{
	t_dt		data;
	va_list		ap;
/* 	char		*s; */
/* 	int			i; */
/* 	char		c; */

	ft_memset(&data, 0, sizeof(data));
	data.head = (char *)format;
	data.tail = (char *)format;
	va_start(ap, format);
	while (*data.tail)
	{
		if (*data.tail == '%')
		{
			if (new_arg(&data) == NULL)
				return (-1);
			data.ret += (data.tail - data.head);
			data.head = data.tail;
			data.tail++;
			while (*data.tail && (*data.tail == ' ' || *data.tail == '+'))
				data.tail++;
			if ((*data.tail >= '0' && *data.tail <= '9') || *data.tail == '-' || *data.tail == '.')
				get_padding(&data);
			if (*data.tail == '%')
			{
				data.ret += 1;
				if (data.last->pad_left > 1)
					data.ret += (data.last->pad_left - 1);
				if (-data.last->pad_left > 1)
					data.ret += (-data.last->pad_left - 1);
			}
			else if (*data.tail == 'x' || *data.tail == 'X')
			{
				get_args_x(&data, &ap);
				if (*data.tail == 'X')
					ft_strtoupper(data.last->s);
				data.ret += data.last->len;
				if (data.last->pad_left > data.last->len)
					data.ret += (data.last->pad_left - data.last->len);
				if (-data.last->pad_left > data.last->len)
					data.ret += (-data.last->pad_left - data.last->len);
				
			}
		}
		else
			data.ret++;
		data.tail++;
	}
	if ((data.buff = ft_strnew(data.ret)) == NULL)
		return (-1);
	data.head = (char *)format;
	data.tail = (char *)format;
	data.last = data.args;

	while (*data.tail)
	{
		if (*data.tail == '%')
		{
			data.head = data.tail;
			data.tail++;
			while (*data.tail && (*data.tail == ' ' || *data.tail == '+'))
				data.tail++;
			while ((*data.tail >= '0' && *data.tail <= '9') || *data.tail == '-' || *data.tail == '.')
				data.tail++;
			if (*data.tail == '%')
			{
				if (data.last->pad_left > 1)
				{
					while (data.last->pad_left-- > 1)
						data.buff = ft_strncat(data.buff, " ", 1);
				}
				data.buff = ft_strncat(data.buff, "%", 1);
				if (-data.last->pad_left > 1)
				{
					while (-(data.last->pad_left++) > 1)
						data.buff = ft_strncat(data.buff, " ", 1);
				}
			}
			else if (*data.tail == 'x' || *data.tail == 'X')
			{
				if (data.last->pad_left > data.last->len)
				{
					while (data.last->pad_left-- > data.last->len)
						data.buff = ft_strncat(data.buff, " ", 1);
				}
				data.buff = ft_strncat(data.buff, data.last->s, data.last->len);
				if (-data.last->pad_left - data.last->len > 1)
				{
					while (-(data.last->pad_left++) > data.last->len)
						data.buff = ft_strncat(data.buff, " ", 1);
				}
			}
			else
				write(STDOUT_FILENO, "s", 1);
			data.last = data.last->next;

		}
		else
			data.buff = ft_strncat(data.buff, data.tail, 1);
		data.tail++;
	}
	if (data.buff)
	{
		write(STDOUT_FILENO, data.buff, data.ret);
		free(data.buff);
	}

/* 	data.buff = (char *)format; */
/* 	while (*data.buff) */
/* 	{ */
/* 		data.pad_left = 0; */
/* 		data.pad_right = 0; */
/* 		if (*data.buff == '%') */
/* 		{ */
/* 			data.buff++; */
/* 			while (*data.buff && (*data.buff == ' ' || *data.buff == '+')) */
/* 				data.buff++; */
/* 			if ((*data.buff >= '0' && *data.buff <= '9') || *data.buff == '-' || *data.buff == '.') */
/* 				get_padding(&data); */
/* 			if (*data.buff == 's') */
/* 			{ */
/* 				s = va_arg(ap, char *); */
/* 				if (s) */
/* 				{ */

/* 					if ((data.len = ft_strlen(s) - data.pad_right) < 0) */
/* 						data.len = 0; */
/* 					if (data.pad_left > 0) */
/* 					{ */
/* 						while (data.pad_left > data.len) */
/* 						{ */
/* 							data.ret += write(STDOUT_FILENO, " ", 1); */
/* 							data.pad_left--; */
/* 						} */
/* 					} */
/* 					if (data.len > 0) */
/* 					{ */
/* 						if (data.pad_right > 0) */
/* 							data.ret += write(STDOUT_FILENO, s, data.pad_right); */
/* 						else */
/* 							data.ret += write(STDOUT_FILENO, s, data.len); */
/* 					} */
/* 					if (data.pad_left < 0) */
/* 					{ */
/* 						while (-data.pad_left > data.len) */
/* 						{ */
/* 							data.ret += write(STDOUT_FILENO, " ", 1); */
/* 							data.pad_left++; */
/* 						} */
/* 					} */
/* 				} */
/* 				else */
/* 					data.ret += write(STDOUT_FILENO, "(null)", 6 - data.pad_right); */
/* 			} */
/* 			else if (*data.buff == 'd') */
/* 			{ */
/* 				char	plus = 0; */
/* 				char	zero = 0; */
/* 				char	*ptr = data.buff; */

/* 				i = va_arg(ap, int); */
/* 				s = ft_itoa(i); */
/* 				while (*--ptr != '%') */
/* 				{ */
/* 					if (*ptr == ' ' && i >= 0 && plus != '+') */
/* 						plus = ' '; */
/* 					else if (*ptr == '+' && i >= 0) */
/* 						plus = '+'; */
/* 					else if (*ptr == '0') */
/* 						zero = '0'; */
/* 				} */
/* 				ptr = s; */
/* 				if (i < 0 && zero) */
/* 					data.ret += write(STDOUT_FILENO, ptr++, 1); */
/* 				if (plus) */
/* 					data.ret += write(STDOUT_FILENO, &plus, 1); */
/* 				if (data.pad_left > 0) */
/* 				{ */
/* 					data.len = ft_strlen(s); */
/* 					if (plus == '+') */
/* 						data.len++; */
/* 					while (data.len++ < data.pad_left) */
/* 					{ */
/* 						if (zero) */
/* 							data.ret += write(STDOUT_FILENO, "0", 1); */
/* 						else */
/* 							data.ret += write(STDOUT_FILENO, " ", 1); */
/* 					} */
/* 				} */
/* 				data.ret += write(STDOUT_FILENO, ptr, ft_strlen(ptr)); */
/* 				if (data.pad_left < 0) */
/* 				{ */
/* 					data.len = -ft_strlen(s); */
/* 					while (data.len-- > data.pad_left) */
/* 						data.ret += write(STDOUT_FILENO, " ", 1); */
/* 				} */
/* 				free(s); */
/* 			} */
/* 			else if (*data.buff == 'c') */
/* 			{ */
/* 				c = va_arg(ap, int); */
/* 				if (data.pad_left > 0) */
/* 				{ */
/* 					while (data.pad_left > 1) */
/* 					{ */
/* 						data.ret += write(STDOUT_FILENO, " ", 1); */
/* 						data.pad_left--; */
/* 					} */
/* 				} */
/* 				data.ret += write(STDOUT_FILENO, &c, 1); */
/* 				if (data.pad_left < 0) */
/* 				{ */
/* 					while (-data.pad_left > 1) */
/* 					{ */
/* 						data.ret += write(STDOUT_FILENO, " ", 1); */
/* 						data.pad_left++; */
/* 					} */
/* 				} */
/* 			} */
/* 			else if (*data.buff == '%') */
/* 			{ */

/* 				if (data.pad_left > 0) */
/* 				{ */
/* 					while (data.pad_left > 1) */
/* 					{ */
/* 						data.ret += write(STDOUT_FILENO, " ", 1); */
/* 						data.pad_left--; */
/* 					} */
/* 				} */
/* 				data.ret += write(STDOUT_FILENO, "%", 1); */
/* 				if (data.pad_left < 0) */
/* 				{ */
/* 					while (-data.pad_left > 1) */
/* 					{ */
/* 						data.ret += write(STDOUT_FILENO, " ", 1); */
/* 						data.pad_left++; */
/* 					} */
/* 				} */
/* 			} */
/* 		} */
/* 		else */
/* 			data.ret += write(STDOUT_FILENO, data.buff, 1); */
/* 		if (*data.buff) */
/* 			data.buff++; */
/* 	} */
	va_end(ap);
	return (data.ret);
}
