/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_cl_send.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 12:19:37 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/24 16:43:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

void			sv_cl_send_to(t_fd *to, t_buf *buf)
{
	if (buf->tail < buf->head)
	{
		send(to->fd, buf->head, buf->end - buf->head, 0);
		send(to->fd, buf->start, buf->tail - buf->start, 0);
	}
	else
		send(to->fd, buf->head, buf->tail - buf->head, 0);
}
