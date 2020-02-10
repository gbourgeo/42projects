/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_server_recv_data.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 02:21:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/10 16:45:12 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include "cl_main.h"

static int		cl_recv_error(int ret, t_server *sv, t_client *cl)
{
	if (errno == EAGAIN || errno == EWOULDBLOCK)
		return (IS_OK);
	if (ret < 0)
	{
		wattron(cl->ncu.chatwin, COLOR_PAIR(CL_RED));
		wprintw(cl->ncu.chatwin, "**ERROR**: ");
		wattron(cl->ncu.chatwin, COLOR_PAIR(CL_BLUE));
		wprintw(cl->ncu.chatwin, "Recv data: %s\n", strerror(errno));
		wattroff(cl->ncu.chatwin, COLOR_PAIR(CL_BLUE));
		wrefresh(cl->ncu.chatwin);
	}
	cl->printtowin = cl->ncu.chatwin;
	cl_server_close(sv, 0, cl);
	return (IS_OK);
}

int				cl_server_recv_data(t_server *sv, t_client *cl)
{
	char		buff[DATA_BUFF_SIZE];
	int			ret;
	int			err;

	ret = recv(sv->fd_data, buff, sizeof(buff), MSG_DONTWAIT | MSG_NOSIGNAL);
	if (ret <= 0)
		return (cl_recv_error(ret, sv, cl));
	if (sv->filename != NULL)
	{
		if (sv->filefd < 0
		&& (sv->filefd = open(sv->filename, O_CREAT | O_TRUNC | O_WRONLY)) < 0)
			return (cl_recv_error(-1, sv, cl));
		err = (write(sv->filefd, buff, ret) != ret) ? ERR : OK;
	}
	else
	{
		err = wprintw(cl->printtowin, "%.*s", ret, buff);
		wrefresh(cl->printtowin);
	}
	return ((err == OK) ? IS_OK : ERR_WRITE);
}
