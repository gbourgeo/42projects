/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_server_recv_data.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 02:21:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/05 22:35:59 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <sys/socket.h>
#include "cl_main.h"

static int		cl_recv_error(int *fd)
{
	if (errno == EAGAIN || errno == EWOULDBLOCK)
		return (IS_OK);
	ft_close(fd);
	return (IS_OK);
}

int				cl_server_recv_data(t_server *sv, t_client *cl)
{
	char		buff[DATA_BUFF_SIZE];
	int			ret;
	int			err;

	ret = recv(sv->fd_data, buff, sizeof(buff), MSG_DONTWAIT | MSG_NOSIGNAL);
	if (ret <= 0)
		return (cl_recv_error(&sv->fd_data));
	err = wprintw(cl->ncu.chatwin, "%.*s", ret, buff);
	wrefresh(cl->ncu.chatwin);
	return ((err == OK) ? IS_OK : ERR_WRITE);
}
