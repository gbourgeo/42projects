/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_response.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 21:32:13 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/21 00:17:30 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "sv_main.h"

typedef struct	s_option
{
	char		value;
	int			(*fct)(t_client *, va_list *);
}				t_option;

static int		sv_response_s(t_client *cl, va_list *ap)
{
	char		*ret;

	ret = va_arg(*ap, char *);
	if (ret)
		return (sv_client_write(ret, cl));
	return (sv_client_write("(null)", cl));
}

static int		sv_response_d(t_client *cl, va_list *ap)
{
	long		ret;
	char		*nb;
	int			errnb;

	ret = va_arg(*ap, long);
	nb = ft_itoa(ret);
	if (!nb)
		return (ERR_MALLOC);
	errnb = sv_client_write(nb, cl);
	free(nb);
	return (errnb);
}

static t_option	*sv_response_opt(char c)
{
	static t_option	opt[] = {
		{ 's', sv_response_s }, { 'd', sv_response_d },
	};
	long			i;

	i = sizeof(opt) / sizeof(opt[0]);
	while (--i >= 0)
		if (opt[i].value == c)
			return (opt + i);
	return (NULL);
}

int				sv_response(t_client *cl, const char *msg, ...)
{
	va_list		ap;
	int			start;
	int			end;
	int			errnb;
	t_option	*opt;

	va_start(ap, msg);
	errnb = IS_OK;
	start = 0;
	end = 0;
	while (msg[end] && errnb == IS_OK)
	{
		if (msg[end] == '%')
		{
			if ((errnb = sv_client_nwrite(msg + start, end - start, cl)))
				break ;
			if ((opt = sv_response_opt(msg[end + 1])))
			{
				errnb = opt->fct(cl, &ap);
				end++;
			}
			else
				errnb = sv_client_nwrite(msg + end, 1, cl);
			start = end + 1;
		}
		end++;
	}
	if (errnb == IS_OK
	&& (errnb = sv_client_nwrite(msg + start, end - start, cl)) == IS_OK)
		errnb = sv_client_write("\r\n", cl);
	va_end(ap);
	return (errnb);
}
