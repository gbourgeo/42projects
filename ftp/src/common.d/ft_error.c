/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/20 08:14:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/21 14:07:37 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# define _POSIX_C_SOURCE 200809L
#endif
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "common.h"
#include "libft.h"

int					ft_error(int errnb, t_common *info)
{
	const char	*err;

	if ((err = ft_get_error(errnb)))
	{
		if (info)
		{
			dprintf(STDERR_FILENO, "%s: %s", info->progname, err);
			if (errno)
				dprintf(STDERR_FILENO, ": %s", strerror(errno));
			dprintf(STDERR_FILENO, ".\n");
		}
		if (*err == '-')
			return (2);
	}
	return (1);
}

static const char	*get_error_next(int errnb)
{
	static const char	*errors[] = {
		"ncurse: init text win failed", "ncurse: init list box failed",
		"ncurse: init list win failed", "ncurse: init chat box failed",
		"ncurse: init chat win failed", "read failed", "open terminal failed",
		"tcgetattr failed", "tcsetattr failed", "Quit",
		"Specify a terminal type", "Could not access the termcap data base",
		"Terminal type is not defined", "pipe failed",
		"Already connected to a server",
	};

	if (errnb < (int)(sizeof(errors) / sizeof(errors[0])))
		return (errors[errnb]);
	return (NULL);
}

const char			*ft_get_error(int errnb)
{
	static const char	*errors[] = {
		"Bye.", "-- Help", "Missing parameter",
		"Wrong parameter", "Invalid parameter",
		"parameter contains non digit characters",
		"too much paramaters given", "getaddrinfo failed",
		"port already in use (v4)", "port already in use (v6)",
		"setsockopt failed", "listen(AF_INET) failed", "open failed",
		"listen(AF_INET6) failed", "malloc failed", "select failed",
		"accept IP_V4 failed", "accept IP_V6 failed", "recv failed",
		"disconnected from server", "signal received", "wait failed",
		"fork failed", "dup2 failed", "execv failed", "send failed",
		"invalid username/password", "failed to change working directory",
		"invalid command", "user already registered", "write failed",
		"users file not found", "get_next_line failed",
		"connection failed", "Unable to open port",
		"DATA header corrupted", "transfert timed out", "lseek failed",
		"mmap failed", "fstat failed", "not valid file", "no server found",
		"ncurse: init main win failed", "ncurse: init text box failed",
	};

	if (errnb < 0)
		return (NULL);
	if (errnb < (int)(sizeof(errors) / sizeof(errors[0])))
		return (errors[errnb]);
	return (get_error_next(errnb - (int)(sizeof(errors) / sizeof(errors[0]))));
}
