/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reporter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 22:47:39 by root              #+#    #+#             */
/*   Updated: 2018/10/01 09:28:48 by root             ###   ########.fr       */
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

int				hireReporter()
{
	e.server.reporter = open(SERVER_REPORTER, O_CREAT | O_TRUNC | O_RDWR, 0600);
	return e.server.reporter >= 0;
}

void			serverLog(const char *message, ...)
{
	time_t		t;
	struct tm	*tm;
	char		buf[25];
	va_list		ap;
	size_t		i, j;

	if (e.server.reporter < 0)
		return ;
	t = time(NULL);
	tm = localtime(&t);
	strftime(buf, 25, "[%d/%m/%Y - %H:%M:%S] ", tm);
	write(e.server.reporter, buf, mystrlen(buf));
	va_start(ap, message);
	i = j = 0;
	while (message[i]) {
		if (message[i] == '%') {
			if (i != j)
				write(e.server.reporter, &message[j], i - j);
			j = i + 2;
			if (message[i+1] == 'd') {
				char *ptr;
				if ((ptr = myitoa(va_arg(ap, int))) != NULL) {
					write(e.server.reporter, ptr, mystrlen(ptr));
					free(ptr);
				}
			} else if (message[i+1] == 's') {
				char *ptr = va_arg(ap, char *);
				write(e.server.reporter, ptr, mystrlen(ptr));
			} else if (message[i+1] == 'p') {
				char *ptr;
				if ((ptr = myitoa(va_arg(ap, unsigned long long))) != NULL) {
					write(e.server.reporter, ptr, mystrlen(ptr));
					free(ptr);
				}
			} else {
				write(e.server.reporter, &message[i], 2);
			}
			i++;
		}
		i++;
	}
	write(e.server.reporter, &message[j], i - j);
	write(e.server.reporter, "\n", 1);
}
