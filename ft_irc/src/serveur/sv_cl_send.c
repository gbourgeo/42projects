/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_cl_send.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 12:19:37 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/27 18:50:15 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

void			sv_cl_send_to(t_fd *to, t_buf *buf)
{
	char		ptr[BUFF + 1];

	if (buf->tail < buf->head)
	{
		ft_strncpy(ptr, buf->head, buf->end - buf->head);
		ft_strncat(ptr, buf->start, buf->tail - buf->start);
		send(to->fd, ptr, ft_strlen(ptr), 0);
	}
	else
		send(to->fd, buf->head, buf->tail - buf->head, 0);
}
