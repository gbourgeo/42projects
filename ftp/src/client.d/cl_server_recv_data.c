/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_server_recv_data.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 02:21:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/20 21:26:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "cl_main.h"

static int		cl_recv_error(t_server *sv)
{
	if (errno == EAGAIN || errno == EWOULDBLOCK)
		return (IS_OK);
	return ((sv->ret-- < 0) ? ERR_RECV : IS_OK);
}

int				cl_server_recv_data(t_server *sv, t_client *cl)
{
	char		buff[DATA_BUFF_SIZE];
	int			err;

	sv->ret = recv(sv->fd_data, buff, sizeof(buff),
		MSG_DONTWAIT | MSG_NOSIGNAL);
	if (sv->ret <= 0)
		return (cl_recv_error(sv));
	if (sv->filename != NULL)
	{
		wprintw(cl->ncu.chatwin, "Opening file : %s\n", sv->filename);
		wrefresh(cl->ncu.chatwin);
		if (sv->filefd < 0
		&& (sv->filefd = open(sv->filename, O_CREAT | O_TRUNC | O_WRONLY,
			0644)) < 0)
			return (cl_recv_error(sv));
		err = (write(sv->filefd, buff, sv->ret) != sv->ret) ? ERR : OK;
	}
	else
	{
		err = wprintw(cl->printtowin, "%.*s", sv->ret, buff);
		wrefresh(cl->printtowin);
	}
	return ((err == OK) ? IS_OK : ERR_WRITE);
}
