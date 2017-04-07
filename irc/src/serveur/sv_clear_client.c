/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_clear_client.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 21:57:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/07 04:43:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <stdio.h>

static void		sv_free_client_onchans(t_fd *cl, t_listin *chan)
{
	t_listin	*list;

	if (!chan)
		return ;
	list = ((t_chan *)chan->is)->users;
	while (list)
	{
		if (((t_fd *)list->is)->fd == cl->fd)
		{
			(cl->inf->umode & USR_INVISIBL) ? ((t_chan *)chan->is)->invisibl-- :
				((t_chan *)chan->is)->nbusers--;
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
	sv_free_client_onchans(cl, chan->next);
	ft_memset(chan, 0, sizeof(*chan));
	free(chan);
}

static void		sv_free_client(t_fd *cl, t_env *e)
{
	if (!cl->inf->pass)
	{
		ft_free(&cl->inf->realname);
		free(cl->inf);
		cl->inf = NULL;
	}
	if (cl->away)
		free(cl->away);
	if (cl->queue)
		free(cl->queue);
	if (cl->prev)
		cl->prev->next = cl->next;
	else
		e->fds = cl->next;
	if (cl->next)
		cl->next->prev = cl->prev;
}

static void		sv_send_reason(t_fd *cl)
{
	sv_cl_write("ERROR :Closing Link: ", cl);
	sv_cl_write(cl->inf->nick, cl);
	sv_cl_write("[~", cl);
	sv_cl_write(cl->inf->username, cl);
	sv_cl_write("@", cl);
	sv_cl_write((*cl->host) ? cl->host : cl->addr, cl);
	sv_cl_write("] (", cl);
	sv_cl_write(cl->reason, cl);
	if (cl->leaved == 2)
	{
		sv_cl_write("[~", cl);
		sv_cl_write(cl->inf->username, cl);
		sv_cl_write("]", cl);
	}
	sv_cl_write(")", cl);
	sv_cl_write(END_CHECK, cl);
	cl->reason = NULL;
}

t_fd			*sv_clear_client(t_env *e, t_fd *cl)
{
	t_fd		*next;

	next = cl->next;
	if (cl->reason)
	{
		if (e->verb)
			printf("%s(%s):%s :%s\n", cl->addr, cl->host, cl->port, cl->reason);
		sv_send_reason(cl);
		return (cl);
	}
	FD_CLR(cl->fd, &e->fd_read);
	FD_CLR(cl->fd, &e->fd_write);
	if (cl->inf->registered > 0)
		e->members--;
	sv_free_client_onchans(cl, cl->chans);
	sv_free_client(cl, e);
	close(cl->fd);
	ft_memset(cl, 0, sizeof(*cl));
	free(cl);
	cl = NULL;
	return (next);
}
