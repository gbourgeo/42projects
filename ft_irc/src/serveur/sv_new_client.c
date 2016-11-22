/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_new_client.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 17:26:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/07/26 17:50:51 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <stdio.h>
#include <time.h>

static void			sv_print(t_env *e, t_fd *cl)
{
	t_fd			*tmp;

	tmp = e->fds;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (tmp == NULL)
		e->fds = cl;
	else
	{
		tmp->next = cl;
		cl->prev = tmp;
	}
	if (e->verb)
		printf("\e[32mNew client from\e[0m %s :%s\n", cl->addr, cl->port);
	send(cl->fd, ":Welcome to the Internet Relay Chat ", 36, 0);
	send(cl->fd, cl->nick, NAME_SIZE, 0);
	send(cl->fd, "\n:Your host is ", 15, 0);
	send(cl->fd, e->name, NAME_SIZE, 0);
	send(cl->fd, "\n:This server was created ", 26, 0);
	send(cl->fd, e->creation, ft_strlen(e->creation), 0);
	send(cl->fd, "\r\n", 2, 0);
	sv_cl_prompt(cl);
}

static void			sv_fill_buf(t_buf *info, char *buff)
{
	info->start = &buff[0];
	info->end = &buff[BUFF];
	info->head = &buff[0];
	info->tail = &buff[0];
	info->len = 0;
}

static void			sv_find_nick(t_env *e, t_fd *new)
{
	t_user			*us;
	size_t			nb;

	us = e->chan->user;
	ft_strncpy(new->nick, "user", NAME_SIZE + 1);
	nb = 0;
	while (us)
	{
		ft_strncpy(new->nick + 4, ft_itoa(nb), NAME_SIZE - 4);
		if (ft_strcmp(new->nick, ((t_fd *)us->is)->nick) == 0)
		{
			nb++;
			us = e->chan->user;
		}
		else
			us = us->next;
	}
	ft_strncpy(new->nick + 4, ft_itoa(nb), NAME_SIZE - 4);
}

int					sv_new_client(t_env *e, t_fd *new)
{
	t_fd			*cl;

	cl = (t_fd *)malloc(sizeof(*cl));
	if (cl == NULL)
		return (1);
	ft_memcpy(cl, new, sizeof(*new));
	cl->type = FD_CLIENT;
	cl->time = time(NULL);
	sv_find_nick(e, cl);
	if ((cl->user = sv_new_user(cl)) == NULL)
	{
		free(cl);
		return (1);
	}
	cl->chan = e->chan;
	cl->fct_read = sv_cl_read;
	cl->fct_write = sv_cl_write;
	sv_fill_buf(&cl->rd, cl->buf_read);
	sv_fill_buf(&cl->wr, cl->buf_write);
	e->chan->nbusers++;
	e->chan->user = sv_add_chan_user(e->chan, cl->user);
	sv_print(e, cl);
	return (0);
}
