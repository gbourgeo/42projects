/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_response.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 21:32:13 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/25 16:26:12 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "sv_main.h"
#include "sv_struct.h"

int				sv_response(t_client *cl, const char *msg, ...)
{
	va_list		ap;
	int			start;
	int			end;
	int			errnb;
	t_ropt		*opt;

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
			if ((opt = sv_response_opt((char *)&msg[end + 1])))
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
