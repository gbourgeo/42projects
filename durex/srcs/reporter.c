/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reporter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 22:47:39 by root              #+#    #+#             */
/*   Updated: 2019/08/04 01:24:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* time */
#include <time.h>
/* write */
#include <unistd.h>
/* ... */
#include <stdarg.h>
/* malloc */
#include <stdlib.h>
/* open */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/* mutex */
#include <pthread.h>

#include "main.h"

int				hireReporter(void)
{
	e.server.reporter = open(SERVER_REPORTER, O_CREAT | O_TRUNC | O_RDWR, 0600);
	pthread_mutex_init(&e.server.mutex, NULL);
	return e.server.reporter >= 0;
}

static void		serverLogTimestamp(int uptime)
{
	time_t		t;
	struct tm	*tm;
	char		buf[25];

	t = (uptime == 2) ? e.server.uptime : time(NULL);
	tm = localtime(&t);
	strftime(buf, 25, "[%d/%m/%Y - %T] ", tm);
	write(e.server.reporter, buf, mystrlen(buf));
}

static void		serverLogPercent(const char *message, va_list *ap, size_t *i, size_t *j)
{
	char *ptr;

	if (*i != *j)
		write(e.server.reporter, &message[*j], *i - *j);
	if (message[*i + 1] == 'd') {
		if ((ptr = myitoa(va_arg(*ap, int))) != NULL) {
			write(e.server.reporter, ptr, mystrlen(ptr));
			free(ptr);
		}
	} else if (message[*i + 1] == 's') {
		ptr = va_arg(*ap, char *);
		write(e.server.reporter, ptr, mystrlen(ptr));
	} else if (message[*i + 1] == 'p') {
		if ((ptr = myitoa(va_arg(*ap, unsigned long long))) != NULL) {
			write(e.server.reporter, ptr, mystrlen(ptr));
			free(ptr);
		}
	} else {
		write(e.server.reporter, &message[*i], 2);
	}
	if (message[++(*i)])
		++(*i);
	*j = *i;
}

static void		serverLogEscaped(const char *message, size_t *i, size_t *j)
{
	if (*i != *j)
		write(e.server.reporter, &message[*j], *i - *j);
	if (message[*i + 1] == 'n') {
		write(e.server.reporter, "\n", 1);
	} else if (message[*i + 1] == 't') {
		write(e.server.reporter, "\t", 1);
	} else {
		write(e.server.reporter, &message[*i], 2);
	}
	if (message[++(*i)])
		++(*i);
	*j = *i;
}

void			serverLog(int ts, const char *message, ...)
{
	va_list		ap;
	size_t		i, j;

	if (e.server.reporter < 0)
		return ;
	pthread_mutex_lock(&e.server.mutex);
	va_start(ap, message);
	i = j = 0;
	if (ts)
		serverLogTimestamp(ts);
	while (message[i]) {
		if (message[i] == '%')
			serverLogPercent(message, &ap, &i, &j);
		else if (message[i] == '\\')
			serverLogEscaped(message, &i, &j);
		else
			i++;
	}
	write(e.server.reporter, &message[j], i - j);
	pthread_mutex_unlock(&e.server.mutex);
}

void			serverClearLogs(t_cl *client)
{
	int			fd;

	pthread_mutex_lock(&e.server.mutex);
	fd = open(SERVER_REPORTER, O_TRUNC | O_RDWR, 0600);
	if (fd < 0)
		clientWrite("Failed to open logs...\n", client);
	else
	{
		close(e.server.reporter);
		e.server.reporter = fd;
		serverLog(2, "[LOGS] - Server online\n");
		serverLog(1, "[LOGS] - Clients :\n");
		for (size_t i = 0; i < SERVER_CLIENT_MAX; i++)
		{
			if (e.server.client[i].fd != -1)
			{
				serverLog(1, "- %d: Online\n", i + 1);
				serverLog(1, "\tAddress: %s\n", e.server.client[i].addr);
				serverLog(1, "\tHost   : %s\n", e.server.client[i].host);
				serverLog(1, "\tPort   : %s\n", e.server.client[i].port);
				serverLog(1, "\tShell  : %s\n", e.server.client[i].shell != -1 ? "Opened" : "Closed");
				serverLog(1, "\tLogged : %s\n", e.server.client[i].logged ? "Yes" : "No");
			}
			else
				serverLog(1, "- %d: Offline\n", i + 1);
		}
		clientWrite("Logs cleared !\n", client);
	}
	pthread_mutex_unlock(&e.server.mutex);
}
