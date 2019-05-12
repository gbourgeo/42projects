/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reporter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 22:47:39 by root              #+#    #+#             */
/*   Updated: 2019/05/12 17:43:46 by gbourgeo         ###   ########.fr       */
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

static void		serverLogTimestamp(void)
{
	time_t		t;
	struct tm	*tm;
	char		buf[25];

	t = time(NULL);
	tm = localtime(&t);
	strftime(buf, 25, "[%d/%m/%Y - %H:%M:%S] ", tm);
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
		serverLogTimestamp();
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
