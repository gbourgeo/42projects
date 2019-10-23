/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_loop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 08:45:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/18 00:49:33 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/select.h>
#include "sv_main.h"

static void		sv_print_error(t_client *cl, t_server *sv)
{
	if (cl->errnb[0] > 0)
		ft_error(cl->errnb[0], &sv->info);
	if (cl->errnb[1] > 0)
		ft_error(cl->errnb[1], &sv->info);
}

static void		sv_check_clients(t_server *sv)
{
	t_client	*cl;

	cl = sv->clients;
	while (cl)
	{
		if (cl->errnb[0] != IS_OK || cl->errnb[1] != IS_OK)
		{
			if (sv->interactive)
				sv_print_error(cl, sv);
			if ((cl->errnb[0] != IS_OK && cl->errnb[0] != ERR_DISCONNECT)
			|| (cl->errnb[1] != IS_OK && cl->errnb[1] != ERR_DISCONNECT))
				return (sv_server_close(cl->version, cl->errnb, sv));
			cl = sv_client_end(cl, sv);
		}
		else
			cl = cl->next;
	}
}

static int		sv_init_fd(fd_set *fdr, fd_set *fdw, t_server *sv)
{
	t_client	*cl;
	int			max;

	cl = sv->clients;
	max = (sv->ip[v4] > sv->ip[v6]) ? sv->ip[v4] : sv->ip[v6];
	FD_ZERO(fdr);
	FD_ZERO(fdw);
	if (sv->ip[v4] > 0)
		FD_SET(sv->ip[v4], fdr);
	if (sv->ip[v6] > 0)
		FD_SET(sv->ip[v6], fdr);
	while (cl)
	{
		FD_SET(cl->fd, fdr);
		FD_SET(cl->fd, fdw);
		if (cl->fd > max)
			max = cl->fd;
		cl = cl->next;
	}
	return (max);
}

static void		sv_check_fd(int ret, fd_set *fdr, fd_set *fdw, t_server *sv)
{
	t_client	*cl;
	int			errnb[2];

	cl = sv->clients;
	errnb[0] = IS_OK;
	errnb[1] = IS_OK;
	if (sv->ip[v4] > 0 && FD_ISSET(sv->ip[v4], fdr))
		if ((errnb[0] = sv_accept(v4, sv)) != IS_OK)
			sv_server_close(v4, errnb, sv);
	if (sv->ip[v6] > 0 && FD_ISSET(sv->ip[v6], fdr))
		if ((errnb[1] = sv_accept(v6, sv)) != IS_OK)
			sv_server_close(v6, errnb, sv);
	while (cl && ret)
	{
		if (FD_ISSET(cl->fd, fdr))
			cl->errnb[0] = cl->fct_read(cl, sv);
		if (FD_ISSET(cl->fd, fdw))
			cl->errnb[1] = cl->fct_write(cl, sv);
		if (FD_ISSET(cl->fd, fdr) || FD_ISSET(cl->fd, fdw))
			ret--;
		cl = cl->next;
	}
}

int				sv_loop(t_server *sv)
{
	int				max;
	int				ret;
	fd_set			fd_read;
	fd_set			fd_write;
	struct timeval	timeout;

	if (sv->interactive)
		ft_putendl("\e[1;33mSERVEUR: Waiting for clients...\e[0m");
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	while (sv->ip[v4] > 0 && sv->ip[v6] > 0)
	{
		sv_check_clients(sv);
		max = sv_init_fd(&fd_read, &fd_write, sv);
		ret = select(max + 1, &fd_read, &fd_write, NULL, &timeout);
		if (ret == -1)
			return (ERR_SELECT);
		if (ret)
			sv_check_fd(ret, &fd_read, &fd_write, sv);
	}
	return (IS_OK);
}
