/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_response_opt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:28:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/25 20:57:03 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "sv_main.h"
#include "sv_struct.h"

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

t_ropt			*sv_response_opt(char *msg)
{
	static t_ropt	opt[] = {
		{ 's', sv_response_s }, { 'd', sv_response_d },
	};
	long			i;

	i = sizeof(opt) / sizeof(opt[0]);
	while (--i >= 0)
		if (opt[i].value == *msg)
			return (opt + i);
	return (NULL);
}
