/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_server_recv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 16:48:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/09 00:39:21 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <sys/socket.h>
#include "cl_main.h"

static int		cl_recv_error(int errnb)
{
	if (errnb == 0 || errno == ECONNRESET || errno == EPIPE)
		return (ERR_DISCONNECT);
	if (errno == EAGAIN || errno == EWOULDBLOCK)
		return (IS_OK);
	return (ERR_RECV);
}

int				cl_server_recv(t_buff *ring, int fd, t_client *cl)
{
	int			ret;

	(void)cl;
	ret = recv(fd, ring->tail, ring->len, MSG_DONTWAIT | MSG_NOSIGNAL);
	if (ret <= 0)
		return (cl_recv_error(ret));
	ring->tail += ret;
	return (IS_OK);
}
