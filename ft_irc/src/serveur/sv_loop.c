/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 08:45:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/11 21:46:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/select.h>

static void			sv_check_fd(t_env *e, int ret)
{
	t_fd			*cl;

	cl = e->fds;
	if (FD_ISSET(e->ipv4, &e->fd_read))
		sv_accept(e, 0);
	if (FD_ISSET(e->ipv6, &e->fd_read))
		sv_accept(e, 1);
	while (cl && ret > 0)
	{
		if (cl->type != FD_FREE)
		{
			if (FD_ISSET(cl->fd, &e->fd_write))
				cl->fct_write(e, cl);
			if (FD_ISSET(cl->fd, &e->fd_read))
				cl->fct_read(e, cl);
			if (FD_ISSET(cl->fd, &e->fd_read) ||
				FD_ISSET(cl->fd, &e->fd_write))
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
	max = (e->ipv4 > e->ipv6) ? e->ipv4 : e->ipv6;
	FD_ZERO(&e->fd_read);
	FD_ZERO(&e->fd_write);
	FD_SET(e->ipv4, &e->fd_read);
	FD_SET(e->ipv6, &e->fd_read);
	while (cl)
	{
		if (cl->type != FD_FREE)
		{
			if (cl->fct_read)
				FD_SET(cl->fd, &e->fd_read);
			if (cl->fct_write)
				FD_SET(cl->fd, &e->fd_write);
			if (cl->fd > max)
				max = cl->fd;
		}
		cl = cl->next;
	}
	return (max);
}

static void			sv_check_clients(t_env *e)
{
	t_fd			*cl;

	cl = e->fds;
	while (cl)
	{
		if (cl->leaved)
			cl = sv_clear_client(e, cl);
		else
			cl = cl->next;
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
		max = sv_init_fd(e);
		ret = select(max + 1, &e->fd_read, &e->fd_write, NULL, NULL);
		if (ret == -1)
			sv_error("Server: ERROR: select()", e);
		if (ret)
			sv_check_fd(e, ret);
	}
	return (0);
}
