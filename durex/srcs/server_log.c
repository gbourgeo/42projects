/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_log.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 00:31:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/08/06 00:35:58 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* time */
#include <time.h>
/* va_arg */
#include <stdarg.h>
/* free */
#include <stdlib.h>
/* mutex */
#include <pthread.h>

#include "main.h"

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
