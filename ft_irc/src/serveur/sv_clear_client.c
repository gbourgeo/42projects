/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_clear_client.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 21:57:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/18 03:52:39 by gbourgeo         ###   ########.fr       */
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

//ERROR :Closing Link: 78.252.122.166 (Invalid username [~&toto])

static void		sv_send_reason(t_fd *cl)
{
	send(cl->fd, "ERROR :Closing Link: ", 21, 0);
	send(cl->fd, cl->addr, ADDR_LEN, 0);
	send(cl->fd, " (", 2, 0);
	send(cl->fd, cl->reason, ft_strlen(cl->reason), 0);
	if (cl->leaved == 2)
	{
		send(cl->fd, "[~", 2, 0);
		send(cl->fd, cl->reg.username, USERNAME_LEN, 0);
		send(cl->fd, "]", 1, 0);
	}
	send(cl->fd, ")", 1, 0);
	send(cl->fd, END_CHECK, END_CHECK_LEN, 0);
}

t_fd			*sv_clear_client(t_env *e, t_fd *cl)
{
	t_fd		*ret;

	FD_CLR(cl->fd, &e->fd_read);
	FD_CLR(cl->fd, &e->fd_write);
	sv_send_reason(cl);
	sv_free_client(cl, e);
	close(cl->fd);
	if (e->verb)
		printf("CLIENT: %s|%s :Has left\n", cl->addr, cl->port);
	ret = cl->next;
	if (cl->reg.registered > 0)
		e->members--;
	ft_memset(cl, 0, sizeof(*cl));
	free(cl);
	cl = NULL;
	return (ret);
}
