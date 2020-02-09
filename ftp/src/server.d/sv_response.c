/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_response.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 21:32:13 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/08 18:47:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "sv_main.h"
#include "sv_struct.h"

static int		sv_response_alt(const char *msg, int i[], t_client *cl,
va_list *ap)
{
	t_ropt		*opt;
	int			errnb;

	if ((errnb = sv_client_nwrite(msg + i[0], i[1] - i[0], cl)) != IS_OK)
		return (errnb);
	if ((opt = sv_response_opt((char *)&msg[i[1] + 1])))
	{
		errnb = opt->fct(cl, ap);
		(i[1])++;
	}
	else
		errnb = sv_client_nwrite(msg + i[1], 1, cl);
	i[0] = i[1] + 1;
	return (errnb);
}

int				sv_response(t_client *cl, const char *msg, ...)
{
	va_list		ap;
	int			i[2];
	int			errnb;

	va_start(ap, msg);
	errnb = IS_OK;
	i[0] = 0;
	i[1] = 0;
	while (msg[i[1]] && errnb == IS_OK)
	{
		if (msg[i[1]] == '%')
			errnb = sv_response_alt(msg, i, cl, &ap);
		i[1]++;
	}
	if (errnb == IS_OK
	&& (errnb = sv_client_nwrite(msg + i[0], i[1] - i[0], cl)) == IS_OK)
		errnb = sv_client_write("\n", cl);
	va_end(ap);
	return (errnb);
}
