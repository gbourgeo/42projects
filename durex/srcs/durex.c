/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   durex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 02:43:33 by root              #+#    #+#             */
/*   Updated: 2018/07/20 17:41:05 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* open */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "main.h"
#include "durex.h"

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

	e.server.reporter = hireReporter();
	e.server.fd = openServer(SERVER_ADDR, SERVER_PORT);
	for (int i = 0; i < SERVER_CLIENT_MAX; i++)
		clearClient(&e.server.client[i]);
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
	quitClearlyServer();
}
