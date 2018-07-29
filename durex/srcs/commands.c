/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 23:22:39 by root              #+#    #+#             */
/*   Updated: 2018/07/29 10:24:01 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* wait */
#include <wait.h>

#include "ft_dprintf.h"

#include "durex.h"

void			serverHelp(t_cl *client, t_cmd *cmds)
{
	for (size_t i = 0; cmds[i].name; i++) {
		clientWrite(cmds[i].name, client);
		clientWrite(": ", client);
		clientWrite(cmds[i].def, client);
		clientWrite("\n", client);
	}
}

void			serverShell(t_cl *client, t_cmd *cmds)
{
	pid_t		pid;
	int			status;

	(void)cmds;
	ft_dprintf(client->fd, "Spawning shell on port %s\n", SERVER_PORT);
	pid = fork();
	if (pid > 0) {
		waitpid(pid, &status, WNOHANG);
	} else if (pid == 0) {
		char		*cmd[3];

		dup2(client->fd, STDIN_FILENO);
		dup2(client->fd, STDOUT_FILENO);
		dup2(client->fd, STDERR_FILENO);
		cmd[0] = "/bin/sh";
		cmd[1] = "-i";
		cmd[2] = NULL;
		execv(cmd[0], cmd);
		clientWrite("$> ", client);
		exit(0);
	} else {
		clientWrite("Failed to fork shell\n", client);
	}
}

void			serverQuitClient(t_cl *client, t_cmd *cmds)
{
	(void)cmds;
	close(client->fd);
	clearClient(client);
}
