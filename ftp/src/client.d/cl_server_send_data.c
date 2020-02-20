/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_server_send_data.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:16:40 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/20 13:50:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "cl_main.h"

static int		cl_send_error(t_server *sv)
{
	if (errno == EAGAIN || errno == EWOULDBLOCK)
		return (IS_OK);
	return ((sv->ret-- < 0) ? ERR_SEND : IS_OK);
}

int				cl_server_send_data(t_server *sv, t_client *cl)
{
	char		buff[DATA_BUFF_SIZE];
	int			nb;

	(void)cl;
	sv->ret = read(sv->filefd, buff, sizeof(buff));
	if (sv->ret <= 0)
		return (cl_send_error(sv));
	nb = sv->ret;
	sv->ret = send(sv->fd_data, buff, sv->ret, MSG_DONTWAIT | MSG_NOSIGNAL);
	if (sv->ret <= 0)
		return (cl_send_error(sv));
	if (sv->ret != nb && (sv->ret = -1))
		return (cl_send_error(sv));
	return (IS_OK);
}
