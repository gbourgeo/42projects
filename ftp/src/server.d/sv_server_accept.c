/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_server_accept.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 05:44:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/10 19:03:37 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include "sv_main.h"

static int		accept_client(int version, int fd, t_server *sv)
{
	t_client	*cl;

	if (!(cl = ft_memalloc(sizeof(*cl))))
		return (ERR_MALLOC);
	cl->version = version;
	cl->fd = fd;
	if (sv_client_init(cl, sv) != IS_OK)
	{
		sv_client_end(cl, sv);
		return (IS_OK);
	}
	if ((cl->next = sv->clients))
		cl->next->prev = cl;
	sv->clients = cl;
	if (FT_CHECK(sv->options, sv_interactive))
		printf("Client "FTP_GREEN"%d"FTP_RESET": %d connected to %s.\n",
		cl->fd, version, cl->home);
	sv_welcome(cl, sv);
	return (IS_OK);
}

int				sv_server_accept(int version, t_server *sv)
{
	int				fd;
	struct sockaddr	csin;
	socklen_t		len;

	len = sizeof(csin);
	if ((fd = accept(sv->ip[version], &csin, &len)) < 0)
		return ((version == sv_v4) ? ERR_ACCEPT_V4 : ERR_ACCEPT_V6);
	if (fd >= FD_SETSIZE)
	{
		send(fd, "421 Server Busy. Come back later !\n", 36, 0);
		close(fd);
		return (IS_OK);
	}
	if (sv->connected + 1 == CLIENTS_MAX)
	{
		send(fd, "421 Server Full. Come back later !\n", 36, 0);
		close(fd);
		return (IS_OK);
	}
	sv->connected++;
	return (accept_client(version, fd, sv));
}
