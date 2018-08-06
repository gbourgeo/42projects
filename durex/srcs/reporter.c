/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reporter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 22:47:39 by root              #+#    #+#             */
/*   Updated: 2018/08/06 19:35:08 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* time */
#include <time.h>
/* write */
#include <unistd.h>

static int		len(const char *s)
{
	char		*p = (char *)s;

	while (*p)
		p++;
	return (p - s);
}

void			serverLog(int fd, const char *message)
{
	time_t		t;
	struct tm	*tm;
	char		buf[25];

	if (fd < 0)
		return ;
	t = time(NULL);
	tm = localtime(&t);	
	strftime(buf, 25, "[%d/%m/%Y - %H:%M:%S] ", tm);
	write(fd, buf, len(buf));
	write(fd, message, len(message));
	write(fd, "\n", 1);
}
