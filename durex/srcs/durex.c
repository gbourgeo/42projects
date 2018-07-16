/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   durex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 02:43:33 by root              #+#    #+#             */
/*   Updated: 2018/07/16 17:36:12 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "durex.h"

static int			setupSelect(t_sv *server)
{
	int				i;
	int				max;

	FD_ZERO(&server->fdr);
	FD_ZERO(&server->fdw);
	FD_SET(server->fd, &server->fdr);
	max = server->fd;
	i = 0;
	while (i < CLIENT_MAX)
	{
		if (server->client[i].fd > max)
			max = server->client[i].fd;
		if (server->client[i].fd != -1) {
			FD_SET(server->client[i].fd, &server->fdr);
			FD_SET(server->client[i].fd, &server->fdw);
		}
		i++;
	}
	return max;
}

void				durex()
{
	t_sv			server;
	int				maxfd;
	int				ret;
	struct timeval	timeout;

	server.fd = openServer(SERVER_ADDR, SERVER_PORT);
	for (int i = 0; i < CLIENT_MAX; i++)
		clearClient(&server.client[i]);
	while (1)
	{
		maxfd = setupSelect(&server);
		ret = select(maxfd + 1, &server.fdr, &server.fdw, NULL, &timeout);
		if (ret == -1)
			break ;
		if (FD_ISSET(server.fd, &server.fdr))
			serverAcceptConnections(&server);
		for (int i = 0; i < CLIENT_MAX; i++)
		{
			if (server.client[i].fd == -1)
				continue ;
			if (FD_ISSET(server.client[i].fd, &server.fdr))
				serverReadClient(&server.client[i]);
			if (FD_ISSET(server.client[i].fd, &server.fdw))
				serverWriteClient(&server.client[i]);
		}
	}
	quitServer(&server);
}
