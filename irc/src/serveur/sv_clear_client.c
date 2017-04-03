/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_clear_client.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 21:57:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/03 21:32:50 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <stdio.h>

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
	if (!cl->inf->pass)
	{
		ft_free(&cl->inf->realname);
		free(cl->inf);
		cl->inf = NULL;
	}
	if (cl->away)
		free(cl->away);
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
	sv_cl_write(cl->addr, cl);
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
}

t_fd			*sv_clear_client(t_env *e, t_fd *cl)
{
	t_fd		*ret;

	FD_CLR(cl->fd, &e->fd_read);
	FD_CLR(cl->fd, &e->fd_write);
	sv_send_reason(cl);
	sv_free_client_onchans(cl, NULL);
	sv_free_client(cl, e);
	close(cl->fd);
	if (e->verb)
		printf("CLIENT: %s|%s :Has left\n", cl->addr, cl->port);
	ret = cl->next;
	if (cl->registered > 0)
		e->members--;
	ft_memset(cl, 0, sizeof(*cl));
	free(cl);
	cl = NULL;
	return (ret);
}
