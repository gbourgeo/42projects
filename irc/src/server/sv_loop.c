/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 08:45:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/11 08:30:00 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/select.h>

static void			sv_check_fd(t_env *e, int ret)
{
	t_fd			*cl;

	cl = e->fds;
	if (e->v4.fd > 0 && FD_ISSET(e->v4.fd, &e->fd_read))
		sv_accept(e, 0);
	if (e->v6.fd > 0 && FD_ISSET(e->v6.fd, &e->fd_read))
		sv_accept(e, 1);
	while (cl && ret > 0)
	{
		if (cl->type != FD_FREE)
		{
			if (FD_ISSET(cl->i.fd, &e->fd_write))
				cl->fct_write(cl);
			if (FD_ISSET(cl->i.fd, &e->fd_read))
				cl->fct_read(e, cl);
			if (FD_ISSET(cl->i.fd, &e->fd_read) ||
				FD_ISSET(cl->i.fd, &e->fd_write))
				ret--;
		}
		cl = cl->next;
	}
}

static int			sv_init_fd(t_env *e)
{
	t_fd			*cl;
	int				max;

	cl = e->fds;
	max = (e->v4.fd > e->v6.fd) ? e->v4.fd : e->v6.fd;
	FD_ZERO(&e->fd_read);
	FD_ZERO(&e->fd_write);
	if (e->v4.fd > 0)
		FD_SET(e->v4.fd, &e->fd_read);
	if (e->v6.fd > 0)
		FD_SET(e->v6.fd, &e->fd_read);
	while (cl)
	{
		if (cl->type == FD_CLIENT)
		{
			if (cl->fct_write && cl->wr.len > 0)
				FD_SET(cl->i.fd, &e->fd_write);
			else if (cl->fct_read && !cl->leaved)
				FD_SET(cl->i.fd, &e->fd_read);
			if (cl->i.fd > max)
				max = cl->i.fd;
		}
		cl = cl->next;
	}
	return (max);
}

static void			sv_check_chans(t_env *e)
{
	t_chan			*ch;
	t_chan			*next;

	ch = e->chans;
	while (ch)
	{
		next = ch->next;
		if (ch->nbusers + ch->invisibl <= 0)
		{
			if (ch->prev)
				ch->prev->next = ch->next;
			else
				e->chans = ch->next;
			if (ch->next)
				ch->next->prev = ch->prev;
			free(ch);
		}
		ch = next;
	}
}

int					sv_loop(t_env *e)
{
	int				ret;
	int				max;

	if (e->verb)
		ft_putendl("\e[1;33mSERVEUR: Waiting for clients...\e[0m");
	while (1)
	{
		sv_check_clients(e);
		sv_check_chans(e);
		max = sv_init_fd(e);
		ret = select(max + 1, &e->fd_read, &e->fd_write, NULL, NULL);
		if (ret == -1)
			sv_error("Server: ERROR: select()", e);
		if (ret)
			sv_check_fd(e, ret);
	}
	return (0);
}
