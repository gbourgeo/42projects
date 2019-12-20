/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_server_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 08:45:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/19 22:49:09 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# define _DEFAULT_SOURCE
#endif
#include <sys/wait.h>
#include <sys/select.h>
#include "sv_main.h"

static void		sv_check_pid(t_client *cl, t_server *sv)
{
	int			ret;
	int			status;

	(void)sv;
	ret = wait4(cl->pid, &status, WNOHANG, NULL);
	if (ret <= 0 || ret != cl->pid)
	{
		if (ret < 0)
			cl->errnb[0] = ERR_WAIT;
		return ;
	}
	if (WIFEXITED(status))
		cl->errnb[0] = (WEXITSTATUS(status)) ?
			sv_client_write(ERR_OUTPUT, cl) :
			sv_client_write(OK_OUTPUT, cl);
	else if (WIFSIGNALED(status))
		cl->errnb[0] = sv_client_write(ERR_OUTPUT, cl);
#ifdef WCOREDUMP
	else if (WCOREDUMP(status))
		cl->errnb[0] = sv_client_write(ERR_OUTPUT, cl);
#endif
	else if (WSTOPSIG(status) || WIFCONTINUED(status))
		return ;
	cl->pid = 0;
}

static void		sv_check_clients(t_server *sv)
{
	t_client	*cl;

	cl = sv->clients;
	while (cl)
	{
		if (cl->pid > 0)
			sv_check_pid(cl, sv);
		if (cl->errnb[0] != IS_OK || cl->errnb[1] != IS_OK)
		{
			if ((cl->errnb[0] != IS_OK && cl->errnb[0] != ERR_DISCONNECT)
			|| (cl->errnb[1] != IS_OK && cl->errnb[1] != ERR_DISCONNECT))
			{
				sv_server_close(cl->version, cl->errnb, sv);
				cl = sv->clients;
			}
			else
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
	if (sv->ip[sv_v4] > 0 && FD_ISSET(sv->ip[sv_v4], fdr))
		if ((errnb[0] = sv_server_accept(sv_v4, sv)) != IS_OK)
			sv_server_close(sv_v4, errnb, sv);
	if (sv->ip[sv_v6] > 0 && FD_ISSET(sv->ip[sv_v6], fdr))
		if ((errnb[1] = sv_server_accept(sv_v6, sv)) != IS_OK)
			sv_server_close(sv_v6, errnb, sv);
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
		sv_check_clients(sv);
		max = sv_init_fd(&fd_read, &fd_write, sv);
		ret = select(max + 1, &fd_read, &fd_write, NULL, &timeout);
		if (ret < 0)
			return (ERR_SELECT);
		if (ret > 0)
			sv_check_fd(ret, &fd_read, &fd_write, sv);
	}
	return (IS_OK);
}
