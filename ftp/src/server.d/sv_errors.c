/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 20:22:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/20 17:50:12 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "sv_main.h"

int					sv_recv_error(int errnb)
{
	if (errnb == 0 || errno == ECONNRESET || errno == EPIPE)
		return (ERR_DISCONNECT);
	if (errno == EAGAIN || errno == EWOULDBLOCK)
		return (IS_OK);
	return (ERR_RECV);
}

int					sv_send_error(int errnb)
{
	if (errnb == 0 || errno == ECONNRESET || errno == EPIPE)
		return (ERR_DISCONNECT);
	if (errno == EAGAIN || errno == EWOULDBLOCK)
		return (IS_OK);
	return (ERR_SEND);
}
