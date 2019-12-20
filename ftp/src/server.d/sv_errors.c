/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 20:22:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/19 20:53:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "sv_main.h"

int					sv_recv_error(int errnb)
{
	if (errnb == 0 || errno == ECONNRESET)
		return (ERR_DISCONNECT);
	if (errno == EAGAIN || errno == EWOULDBLOCK)
		return (IS_OK);
	return (ERR_RECV);
}

int					sv_send_error(int errnb)
{
	return ((errnb == 0 || errno == ECONNRESET) ? ERR_DISCONNECT :
		(errno == EAGAIN || errno == EWOULDBLOCK) ? IS_OK :
		(errno == EPIPE) ? ERR_DISCONNECT : ERR_SEND);
}