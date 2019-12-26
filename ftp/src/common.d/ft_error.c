/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/20 08:14:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/26 01:24:15 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# define _POSIX_C_SOURCE 200809L
#endif
#include <unistd.h>
#include <stdio.h>
#include "common.h"
#include "libft.h"

int				ft_error(int errnb, t_common *info)
{
	const char	*err;

	if ((err = ft_get_error(errnb)))
	{
		if (info)
			dprintf(STDERR_FILENO, "%s: %s\n", info->progname, err);
		if (*err == '-')
			return (2);
	}
	return (1);
}

const char		*ft_get_error(int errnb)
{
	static const char	*errors[] = {
		"Disconnected.", "-- Help", "Missing parameter",
		"Wrong parameter", "Invalid parameter",
		"parameter contains non digit characters.",
		"only one port can be specified.", "getaddrinfo failed.",
		"port already in use (v4)", "port already in use (v6)",
		"setsockopt failed.", "listen(AF_INET) failed.", "open failed.",
		"listen(AF_INET6) failed.", "malloc failed.", "select failed.",
		"accept IP_V4 failed.", "accept IP_V6 failed.", "recv failed.",
		"disconnected.", "signal received.", "wait failed.",
		"fork failed.", "dup2 failed.", "execv failed", "send failed.",
		"invalid username/password.", "failed to change working directory.",
		"invalid command.", "user already registered", "write failed",
		"users file not found.", "get_next_line failed.",
		"A transfert is already in progress", "Unable to open port",
		"DATA header corrupted", "transfert timed out", "lseek failed",
		"mmap failed", "fstat failed", "not valid file",
	};

	if (errnb < 0 || errnb > (int)(sizeof(errors) / sizeof(errors[0])))
		return (NULL);
	return (errors[errnb]);
}
