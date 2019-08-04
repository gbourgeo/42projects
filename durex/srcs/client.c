/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 03:49:03 by root              #+#    #+#             */
/*   Updated: 2019/08/04 20:52:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "durex.h"

void			clearClient(t_cl *client)
{
	client->fd = -1;
	client->shell = -1;
	mymemset(client->addr, 0, sizeof(client->addr));
	mymemset(client->host, 0, sizeof(client->host));
	mymemset(client->port, 0, sizeof(client->port));
	client->logged = 0;
	mymemset(&client->rd, 0, sizeof(client->rd));
	client->rd.head = &client->rd.buff[0];
	client->rd.tail = client->rd.head;
	mymemset(&client->wr, 0, sizeof(client->wr));
	client->wr.head = &client->wr.buff[0];
	client->wr.tail = client->wr.head;
}

void			clientRead(char *buff, int size, t_cl *client)
{
	int			i;

	i = 0;
	while (i < size) {
		*client->rd.head = buff[i];
		if (*client->rd.head == '\n') {
			serverCommands(client);
			client->rd.head = moveTail(client->rd.head, client->rd.buff, SERVER_CLIENT_BUFF);
			client->rd.tail = client->rd.head;
		} else {
			client->rd.head = moveTail(client->rd.head, client->rd.buff, SERVER_CLIENT_BUFF);
			if (client->rd.head == client->rd.tail) {
				client->rd.tail = moveTail(client->rd.tail, client->rd.buff, SERVER_CLIENT_BUFF);
			}
		}
		i++;
	}
}

void			clientWrite(const char *str, t_cl *client)
{
	if (!str)
		return ;
	while (*str) {
		*client->wr.head = *str;
		client->wr.head = moveTail(client->wr.head, client->wr.buff, SERVER_CLIENT_BUFF);
		if (client->wr.head == client->wr.tail) {
			write(client->fd, client->wr.tail, client->wr.buff + SERVER_CLIENT_BUFF - client->wr.tail);
			client->wr.tail = client->wr.buff;
		}
		str++;
	}
}

void			clientShell(int fds)
{
	struct termios	origin;
	struct termios	exclusive;
	struct rlimit	rlim;

	tcgetattr(fds, &origin);
	exclusive = origin;
	cfmakeraw(&exclusive);
	tcsetattr(fds, TCSANOW, &exclusive);
	if (getrlimit(RLIMIT_NOFILE, &rlim) || rlim.rlim_max == RLIM_INFINITY)
		rlim.rlim_max = 4096;
	for (size_t i = 0; i < rlim.rlim_max; i++) {
		if (i != (size_t)fds)
			close(i);
	}
	dup(fds);
	dup(fds);
	dup(fds);
	close(fds);
	setsid();
	ioctl(0, TIOCSCTTY, 1);
	{
		char *cmd[] = { "/bin/sh", "-i", NULL };
		execvp(cmd[0], cmd);
	}
}
