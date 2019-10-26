/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/20 08:14:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/26 02:22:12 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "common.h"
#include "libft.h"

static void		print_usage(const char *progpath, int progtype)
{
	ft_putstr_fd("\nUsage: ", 2);
	ft_putstr_fd(progpath, 2);
	if (progtype == SERVER)
	{
		ft_putendl_fd(" [-i] [-v4] [-v6] [-p [path]] [port]", 2);
		ft_putendl_fd("\t-i\t\tInteractive server.", 2);
		ft_putendl_fd("\t-v4\t\tIp v4 only.", 2);
		ft_putendl_fd("\t-v6\t\tIp v6 only.", 2);
		ft_putendl_fd("\t-p [path]\tServer working path.", 2);
		ft_putendl_fd("\tport\t\tPort to listen to.", 2);
	}
	if (progtype == CLIENT)
		ft_putendl_fd(" [server_address] [server_port]", 2);
}

int				ft_error(int errnb, t_common *info)
{
	const char	*err;

	if ((err = ft_get_error(errnb)))
	{
		ft_putstr_fd(info->progname, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(err, 2);
		if (info)
			if (*err == '-')
				print_usage(info->progpath, info->progtype);
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
