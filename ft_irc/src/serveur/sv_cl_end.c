/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_cl_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/06/06 22:03:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/15 05:47:27 by gbourgeo         ###   ########.fr       */
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
	return (wr->head - wr->tail);
}

void			sv_cl_end(char **cmds, t_env *e, t_fd *cl)
{
	if (cl->chans)
	{
		if (cmds == NULL || !cmds[1] || sv_move_head(&cl->wr))
			sv_sendto_chan_msg(" :Disconnected.", cl);
/* 		else */
/* 			sv_sendto_chan(cl); */
		sv_leave_chan(e, cl);
	}
	cl->leaved = 1;
}

static void		sv_free_client_onchans(t_fd *cl, t_listin *next)
{
	t_listin	*list;

	while (cl->chans)
	{
		list = ((t_chan *)cl->chans->is)->users;
		while (list)
		{
			if (((t_fd *)list->is)->fd == cl->fd)
			{
				((t_chan *)cl->chans->is)->nbusers--;
				if (list->prev)
					list->prev->next = list->next;
				else
					((t_chan *)cl->chans->is)->users = list->next;
				if (list->next)
					list->next->prev = list->prev;
				free(list);
				break ;
			}
			list = list->next;
		}
		next = cl->chans->next;
		free(cl->chans);
		cl->chans = next;
	}
}

static void		sv_free_client(t_fd *cl, t_env *e)
{
	if (cl->reg.password)
		free(cl->reg.password);
	cl->reg.realname = NULL;
	if (cl->away)
		free(cl->away);
	if (cl->prev)
		cl->prev->next = cl->next;
	else
		e->fds = cl->next;
	if (cl->next)
		cl->next->prev = cl->prev;
	sv_free_client_onchans(cl, NULL);
}

t_fd			*sv_clear_client(t_env *e, t_fd *cl)
{
	t_fd		*ret;

	FD_CLR(cl->fd, &e->fd_read);
	FD_CLR(cl->fd, &e->fd_write);
	close(cl->fd);
	sv_free_client(cl, e);
	ret = cl->next;
	if (cl->reg.registered > 0)
		e->members--;
	ft_memset(cl, 0, sizeof(*cl));
	free(cl);
	cl = NULL;
	if (e->verb)
		printf("\n\e[31mCLIENT\e[0m %s %s \e[31mleft\e[0m\n", cl->addr, cl->port);
	return (ret);
}
