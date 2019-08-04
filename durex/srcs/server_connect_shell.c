/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_connect_shell.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 00:02:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/08/05 00:36:32 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* errno */
#include <errno.h>
#include "durex.h"

static int			getAddrInfo(struct addrinfo **res, char *port, t_cl *client)
{
	struct addrinfo	hints;
	int				ret;

	mymemset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_canonname = NULL;
	hints.ai_addr = NULL;
	hints.ai_next = NULL;
	if ((ret = getaddrinfo(client->addr, port, &hints, res))) {
		serverLog(1, "[ERRO] - %d: %s\n", client->id, gai_strerror(ret));
		clientWrite(gai_strerror(ret), client);
		clientWrite("\n", client);
		return -1;
	}
	return 0;
}

static int			connectError(struct addrinfo *tmp, char *port, t_cl *client)
{
	serverLog(1, "[ERRO] - %d: Failed to connect to %s:%s (%s)\n",
				client->id, client->addr, port,
				(tmp) ? strerror(errno) : "No server found");
	clientWrite("Failed to connect to ", client);
	clientWrite(client->addr, client);
	clientWrite(":", client);
	clientWrite(port, client);
	clientWrite(" (", client);
	clientWrite((tmp) ? strerror(errno) : "No server found", client);
	clientWrite(")\n", client);
	return -1;
}

int					serverConnectShell(t_cl *client, char *port)
{
	struct addrinfo	*res;
	struct addrinfo	*tmp;
	int				fd;

	if (getAddrInfo(&res, port, client) != 0)
		return -1;
	tmp = res;
	while (tmp != NULL)
	{
		fd = socket(tmp->ai_family, tmp->ai_socktype, tmp->ai_protocol);
		if (fd < 0)
			continue ;
		if (connect(fd, tmp->ai_addr, tmp->ai_addrlen) == 0)
			break ;
		close(fd);
		fd = -1;
		tmp = tmp->ai_next;
	}
	freeaddrinfo(res);
	if (tmp == NULL || fd < 0)
		return connectError(tmp, port, client);
	serverLog(1, "[CMDS] - %d: Connection to %s:%s succeeded.\n", client->id, client->addr, port);
	clientWrite("Succesfully Connected\n", client);
	return fd;
}
