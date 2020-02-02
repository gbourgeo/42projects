/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_ncurses_write.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 21:05:21 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/02 04:51:45 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int				cl_ncurses_write(t_buff *ring, t_client *cl)
{
	int		ret;

	if (ring->len >= sizeof(ring->buff))
		return (IS_OK);
	if (ring->tail > ring->head)
	{
		ret = wprintw(cl->ncu.chatwin, "%.*s", ring->tail - ring->head, ring->head);
		ring->len += ring->tail - ring->head;
	}
	else
	{
		ret = wprintw(cl->ncu.chatwin, "%.*s",
		ring->buff + sizeof(ring->buff) - ring->head, ring->head);
		ring->len += ring->buff + sizeof(ring->buff) - ring->head;
	}
	wrefresh(cl->ncu.chatwin);
	if (ret == ERR)
		return (ERR_WRITE);
	ring->head = ring->tail;
	return (IS_OK);
}
