/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 08:45:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/25 18:58:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <sys/select.h>

static void			sv_check_fd(t_env *e, int ret)
{
	size_t			i;
	int				fd;

	i = 0;
	while (i < e->maxfd && ret > 0)
	{
		fd = e->fds[i].fd;
		if (e->fds[i].type != FD_FREE)
		{
			if (FD_ISSET(fd, &e->fd_write))
				e->fds[i].fct_write(e, i);
			if (FD_ISSET(fd, &e->fd_read))
				e->fds[i].fct_read(e, i);
			if (FD_ISSET(fd, &e->fd_read) || FD_ISSET(fd, &e->fd_write))
				ret--;
		}
		i++;
	}
}

static int			sv_init_fd(t_env *e)
{
	size_t			i;
	int				max;

	i = 0;
	max = 0;
	FD_ZERO(&e->fd_read);
	FD_ZERO(&e->fd_write);
	while (i < e->maxfd)
	{
		if (e->fds[i].type != FD_FREE)
		{
			FD_SET(e->fds[i].fd, &e->fd_read);
			if (e->fds[i].fct_write)
				FD_SET(e->fds[i].fd, &e->fd_write);
			if (e->fds[i].fd > max)
				max = e->fds[i].fd;
		}
		i++;
	}
	return (max);
}

int					sv_loop(t_env *e)
{
	int				ret;
	int				max;

	if (e->verb)
		ft_putendl("\e[1;33mSERVEUR: Waiting for clients...\e[0m");
	while (1)
	{
		max = sv_init_fd(e);
		ret = select(max + 1, &e->fd_read, &e->fd_write, NULL, NULL);
		if (ret == -1)
			sv_error("Server: ERROR: select()", e);
		if (ret)
			sv_check_fd(e, ret);
	}
	return (0);
}
