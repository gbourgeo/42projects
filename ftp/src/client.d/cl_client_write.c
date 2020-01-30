/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_client_write.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:56:49 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/30 14:58:12 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include "cl_main.h"

static int	cl_send_error(int errnb)
{
	if (errnb == 0 || errno == ECONNRESET || errno == EPIPE)
		return (ERR_DISCONNECT);
	if (errno == EAGAIN || errno == EWOULDBLOCK)
		return (IS_OK);
	return (ERR_SEND);
}

/*
** Function to send commands to the Server.
*/

int			cl_client_send(char *buf, t_client *cl)
{
	int		off;
	int		len;
	int		ret;

	off = 0;
	len = ft_strlen(buf);
	while (off < len)
	{
		ret = send(cl->server.fd, buf, off, 0);
		if (ret <= 0)
		{
			if ((ret = cl_send_error(ret)) != IS_OK)
				return (ret);
		}
		off += ret;
	}
	return (IS_OK);
}
