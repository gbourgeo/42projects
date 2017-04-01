/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_cl_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 18:43:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/01 23:01:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static void		sv_cl_send(t_fd *to, t_buf *buf)
{
	static char	ptr[BUFF + 1] = { 0 };

	if (buf->tail <= buf->head)
	{
		ft_strncpy(ptr, buf->head, buf->end - buf->head);
		ft_strncat(ptr, buf->start, buf->tail - buf->start);
		send(to->fd, ptr, ft_strlen(ptr), 0);
		ft_strclr(ptr);
	}
	else
		send(to->fd, buf->head, buf->tail - buf->head, 0);
	buf->head = buf->tail;
	buf->len = 0;
}

void			sv_cl_write(char *str, t_fd *cl)
{
	if (!str || !cl)
		return ;
	while (*str)
	{
		*cl->wr.tail = *str;
		cl->wr.tail++;
		if (cl->wr.tail == cl->wr.end)
			cl->wr.tail = cl->wr.start;
		cl->wr.len++;
		if (*str == '\n' || cl->wr.len == BUFF)
			sv_cl_send(cl, &cl->wr);
		str++;
	}
}
