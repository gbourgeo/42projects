/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_ncurses_write.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/01 21:05:21 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/11 23:14:22 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

static void		cl_get_response(char *stop, t_buff *ring, t_server *sv)
{
	int			i;

	i = 0;
	while (ring->head != stop && i < (int)sizeof(sv->response) - 1)
	{
		sv->response[i++] = *ring->head++;
		if (ring->head >= ring->buff + sizeof(ring->buff))
			ring->head = ring->buff;
	}
	sv->response[i] = '\0';
}

int				cl_ncurses_write(t_buff *ring, t_client *cl)
{
	char	*ptr;
	int		ret;

	ptr = ring->head;
	ret = OK;
	if (ring->tail != ring->head)
		while (ptr != ring->tail - (ring->tail == ring->buff + sizeof(ring->buff)))
		{
			if (*ptr++ == '\n')
			{
				cl_get_response(ptr, ring, &cl->server);
				wprintw(cl->ncu.chatwin, "%s", cl->server.response);
				wrefresh(cl->ncu.chatwin);
			}
			if (ptr >= ring->buff + sizeof(ring->buff))
				ptr = ring->buff;
		}
	if (ring->tail >= ring->buff + sizeof(ring->buff))
		ring->tail = ring->buff;
	if (ring->tail >= ring->head)
		ring->len = ring->buff + sizeof(ring->buff) - ring->tail;
	else
		ring->len = ring->head - ring->tail - 1;
	if (ret == ERR)
		return (ERR_WRITE);
	return (IS_OK);
}
