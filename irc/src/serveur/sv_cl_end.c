/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_cl_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 22:03:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/07/31 20:59:22 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/socket.h>
#include <stdio.h>

static int		sv_move_head(t_buf *wr)
{
	while (*wr->head && *wr->head == ' ')
	{
		wr->head++;
		if (wr->head >= wr->end)
			wr->head = wr->start;
	}
	while (*wr->head && *wr->head != ' ')
	{
		wr->head++;
		if (wr->head >= wr->end)
			wr->head = wr->start;
	}
	while (*wr->head && *wr->head == ' ')
	{
		wr->head++;
		if (wr->head >= wr->end)
			wr->head = wr->start;
	}
	return ((wr->head == wr->tail) ? 1 : 0);
}

void			sv_cl_end(char **cmds, t_env *e, t_fd *cl)
{
	if (e->verb)
		printf("\e[31mCLIENT\e[0m %s %s \e[31mleft\e[0m\n", cl->addr, cl->port);
	if (cl->chan)
	{
		if (cmds == NULL || !cmds[1] || sv_move_head(&cl->wr))
			sv_sendto_chan_msg(" :Disconnected.", cl);
		else
			sv_sendto_chan(cl);
		sv_leave_chan(e, cl);
	}
	FD_CLR(cl->fd, &e->fd_read);
	FD_CLR(cl->fd, &e->fd_write);
	close(cl->fd);
	if (cl->away)
		free(cl->away);
	if (cl->user)
		free(cl->user);
	if (cl->prev)
		cl->prev->next = cl->next;
	else
		e->fds = cl->next;
	if (cl->next)
		cl->next->prev = cl->prev;
	ft_memset(cl, 0, sizeof(*cl));
	free(cl);
	e->members--;
}
