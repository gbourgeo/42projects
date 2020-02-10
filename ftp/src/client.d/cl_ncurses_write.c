/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_ncurses_write.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 21:05:21 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/10 22:07:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int				cl_ncurses_write(t_buff *ring, t_client *cl)
{
	int		ret;

	ret = OK;
	if (ring->tail != ring->head)
	{
		if (ring->tail > ring->head)
			ret = wprintw(cl->ncu.chatwin, "%.*s",
			ring->tail - ring->head, ring->head);
		else
			ret = wprintw(cl->ncu.chatwin, "%.*s",
			ring->buff + sizeof(ring->buff) - ring->head, ring->head);
		wrefresh(cl->ncu.chatwin);
		if (cl->server.wait_response)
			cl_ringbuffcat(cl->server.response, sizeof(cl->server.response),
			ring);
	}
	if (ring->tail >= ring->buff + sizeof(ring->buff))
		ring->tail = ring->buff;
	ring->head = ring->tail;
	ring->len = ring->buff + sizeof(ring->buff) - ring->tail;
	if (ret == ERR)
		return (ERR_WRITE);
	return (IS_OK);
}
