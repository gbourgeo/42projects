/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_server_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 08:45:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/05 22:27:28 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/select.h>
#include <time.h>
#include "sv_main.h"

static void		sv_check_clients(t_client *cl, t_server *sv)
{
	while (cl)
	{
		if ((cl->data.pid > 0 && (cl->errnb[3] = sv_check_pid(cl)) != IS_OK)
		|| cl->errnb[0] != IS_OK || cl->errnb[1] != IS_OK
		|| cl->errnb[2] != IS_OK)
			cl = sv_client_end(cl, sv);
		// else if (cl->data.fd > 0
		// && time(NULL) - cl->data.timeout >= TRANSFERT_TIMEOUT)
		// 	cl = sv_client_timeout(cl);
		else
			cl = cl->next;
	}
}

static int		sv_init_fd(fd_set *fdr, fd_set *fdw, t_server *sv)
{
	t_client	*cl;
	int			max;

	cl = sv->clients;
	max = (sv->ip[sv_v4] > sv->ip[sv_v6]) ? sv->ip[sv_v4] : sv->ip[sv_v6];
	FD_ZERO(fdr);
	FD_ZERO(fdw);
	if (sv->ip[sv_v4] > 0)
		FD_SET(sv->ip[sv_v4], fdr);
	if (sv->ip[sv_v6] > 0)
		FD_SET(sv->ip[sv_v6], fdr);
	while (cl)
	{
		FD_SET(cl->fd, fdr);
		FD_SET(cl->fd, fdw);
		if (cl->fd > max)
			max = cl->fd;
		if (cl->data.pasv_fd > 0)
			FD_SET(cl->data.pasv_fd, fdr);
		if (cl->data.pasv_fd > max)
			max = cl->data.pasv_fd;
		cl = cl->next;
	}
	return (max);
}

static void		sv_check_fd(int ret, fd_set *fdr, fd_set *fdw, t_server *sv)
{
	t_client	*cl;

	cl = sv->clients;
	if (sv->ip[sv_v4] > 0 && FD_ISSET(sv->ip[sv_v4], fdr) && ret-- > 0)
		if ((sv->errnb[0] = sv_server_accept(sv_v4, sv)) != IS_OK)
			sv_server_close(sv_v4, 1, sv);
	if (sv->ip[sv_v6] > 0 && FD_ISSET(sv->ip[sv_v6], fdr) && ret-- > 0)
		if ((sv->errnb[1] = sv_server_accept(sv_v6, sv)) != IS_OK)
			sv_server_close(sv_v6, 1, sv);
	while (cl && ret)
	{
		if (FD_ISSET(cl->fd, fdr) && ret-- > 0)
			cl->errnb[0] = cl->fct_read(cl);
		if (FD_ISSET(cl->fd, fdw) && ret-- > 0)
			cl->errnb[1] = cl->fct_write(cl);
		if (cl->data.pasv_fd > 0
		&& FD_ISSET(cl->data.pasv_fd, fdr) && ret-- > 0)
			cl->errnb[2] = sv_listen_from(cl);
		cl = cl->next;
	}
}

int				sv_server_loop(t_server *sv)
{
	int				max;
	int				ret;
	fd_set			fd_read;
	fd_set			fd_write;
	struct timeval	timeout;

	if (FT_CHECK(sv->options, sv_interactive))
		sv_server_info(sv);
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	while (sv->ip[sv_v4] > 0 || sv->ip[sv_v6] > 0)
	{
		sv_check_clients(sv->clients, sv);
		max = sv_init_fd(&fd_read, &fd_write, sv);
		ret = select(max + 1, &fd_read, &fd_write, NULL, &timeout);
		if (ret < 0)
			return (ERR_SELECT);
		if (ret > 0)
			sv_check_fd(ret, &fd_read, &fd_write, sv);
	}
	return (IS_OK);
}
