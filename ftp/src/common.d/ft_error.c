/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/20 08:14:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/26 03:06:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "libft.h"

int				ft_error(int errnb, t_common *info)
{
	const char	*err;

	if ((err = ft_get_error(errnb)))
	{
		if (info)
		{
			ft_putstr_fd(info->progname, 2);
			ft_putstr_fd(": ", 2);
			ft_putendl_fd(err, 2);
		}
		if (*err == '-')
			return (2);
	}
	return (1);
}

const char		*ft_get_error(int errnb)
{
	static const char	*errors[] = {
		"Disconnected.", "-- Missing parameter", "-- Wrong parameter",
		"-- Invalid parameter", "parameter contains non digit characters.",
		"only one port can be specified.", "getaddrinfo failed.",
		"port already in use (v4)", "port already in use (v6)",
		"setsockopt failed.", "listen(AF_INET) failed.", "open failed.",
		"listen(AF_INET6) failed.", "malloc failed.", "select failed.",
		"accept IP_V4 failed.", "accept IP_V6 failed.", "recv failed.",
		"Client disconnected.", "signal received.", "wait failed.",
		"fork failed.", "dup2 failed.", "execv failed", "send failed.",
		"invalid username/password.",
	};

	if (errnb < 0 || errnb > (int)(sizeof(errors) / sizeof(errors[0])))
		return (NULL);
	return (errors[errnb]);
}
