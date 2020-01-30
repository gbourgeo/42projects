/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_server_send.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 18:51:48 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/30 18:47:07 by gbourgeo         ###   ########.fr       */
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

int			cl_server_send(t_client *cl)
{
	return (IS_OK);
}
