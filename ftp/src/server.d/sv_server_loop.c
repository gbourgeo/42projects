/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_server_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 08:45:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/22 03:35:12 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/select.h>
#include "sv_main.h"

static void		sv_check_clients(t_client *client, t_server *sv)
{
	while (client)
	{
		if (client->errnb[0] != IS_OK
		|| client->errnb[1] != IS_OK
		|| client->errnb[2] != IS_OK
		|| (client->pid_ls > 0
			&& (client->errnb[2] = sv_check_pid(&client->pid_ls, client)))
		|| (client->data.pid > 0
			&& (client->errnb[2] = sv_check_pid(&client->data.pid, client))))
			client = sv_client_end(client, sv);
		else
			client = client->next;
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
		if (cl->data.fd > 0)
			FD_SET(cl->data.fd, fdr);
		if (cl->data.fd > max)
			max = cl->data.fd;
		cl = cl->next;
	}
	return (max);
}

static void		sv_check_fd(int ret, fd_set *fdr, fd_set *fdw, t_server *sv)
{
	t_client	*cl;

	cl = sv->clients;
	if (sv->ip[sv_v4] > 0 && FD_ISSET(sv->ip[sv_v4], fdr))
		if ((sv->errnb[0] = sv_server_accept(sv_v4, sv)) != IS_OK)
			sv_server_close(sv_v4, sv);
	if (sv->ip[sv_v6] > 0 && FD_ISSET(sv->ip[sv_v6], fdr))
		if ((sv->errnb[1] = sv_server_accept(sv_v6, sv)) != IS_OK)
			sv_server_close(sv_v6, sv);
	while (cl && ret)
	{
		if (FD_ISSET(cl->fd, fdr))
			cl->errnb[0] = cl->fct_read(cl, sv);
		if (FD_ISSET(cl->fd, fdw))
			cl->errnb[1] = cl->fct_write(cl, sv);
		if (FD_ISSET(cl->fd, fdr) || FD_ISSET(cl->fd, fdw))
			ret--;
		if (cl->data.fd > 0 && FD_ISSET(cl->data.fd, fdr))
		{
			cl->errnb[2] = sv_data_accept(cl, sv);
			ret--;
		}
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

	if (SV_CHECK(sv->options, sv_interactive))
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
