/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_accept.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 05:44:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/25 23:15:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sv_main.h"

static int		accept_client(int version, int fd, t_server *sv)
{
	t_client	*cl;

	if (!(cl = ft_memalloc(sizeof(*cl))))
		return (ERR_MALLOC);
	cl->version = version;
	cl->fd = fd;
	cl->fct_read = sv_client_recv;
	cl->fct_write = sv_client_send;
	cl->rd.head = cl->rd.buff;
	cl->rd.tail = cl->rd.head;
	cl->rd.len = FTP_BUFF_SIZE;
	cl->wr.head = cl->wr.buff;
	cl->wr.tail = cl->wr.head;
	cl->wr.len = 0;
	cl->pwd = ft_strdup("/");
	cl->oldpwd = ft_strdup("/");
	if ((cl->next = sv->clients))
		cl->next->prev = cl;
	sv->clients = cl;
	if (!cl->pwd || !cl->oldpwd)
		return (ERR_MALLOC);
	return (IS_OK);
}

int				sv_accept(int version, t_server *sv)
{
	int				fd;
	struct sockaddr	csin;
	socklen_t		len;

	len = sizeof(csin);
	if ((fd = accept(sv->ip[version], &csin, &len)) < 0)
		return ((version == v4) ? ERR_ACCEPT_V4 : ERR_ACCEPT_V6);
	if (sv->connected + 1 == CLIENTS_MAX)
	{
		send(fd, "Server Full. Come back later !\n", 31, 0);
		close(fd);
		return (IS_OK);
	}
	sv->connected++;
	if (sv->interactive)
		ft_putendl("Client connected");
	return (accept_client(version, fd, sv));
}
