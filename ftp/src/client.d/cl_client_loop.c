/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_client_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 08:44:55 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/08 16:52:32 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/select.h>
#include "cl_main.h"

static int			client_info(t_client *cl)
{
	if (!(cl->server.pwd = ft_strdup("/")))
		return (ERR_MALLOC);
	if (!(cl->pwd = getcwd(NULL, 0)))
		return (ERR_MALLOC);
	cl->success = 1;
	cl->rd.head = cl->rd.buff;
	cl->rd.tail = cl->rd.buff;
	return (IS_OK);
}

static int			init_fdset(fd_set *r, fd_set *w, t_client *cl)
{
	int		max;

	max = 0;
	FD_ZERO(r);
	FD_ZERO(w);
	FD_SET(0, r);
	FD_SET(cl->server.fd, r);
	if (cl->server.fd > max)
		max = cl->server.fd;
	return (max);
}

static void			check_fdset(fd_set *r, fd_set *w, t_client *cl)
{
	if (FD_ISSET(0, r))
		cl->errnb[0] = (FT_CHECK(cl->options, cl_ncurses))
		? cl_ncurses_read : cl_stdin_read;
	if (FD_ISSET(cl->server.fd, r))
		cl->errnb[1] = cl_server_recv(cl);
}

int					cl_client_loop(t_client *cl)
{
	int				max;
	int				ret;
	fd_set			fd_read;
	fd_set			fd_write;
	struct timeval	timeout;
	int				errnb;

	if ((errnb = client_info(cl)) != IS_OK)
		return (errnb);
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	while (1)
	{
		max = init_fdset(&fd_read, &fd_write, cl);
		ret = select(max + 1, &fd_read, &fd_write, NULL, &timeout);
		if (ret < 0)
			return (ERR_SELECT);
		if (ret > 0)
			check_fdset(&fd_read, &fd_write, cl);
	}
	return (IS_OK);
}

void			cl_prompt(t_client *cl)
{
	if (FT_CHECK(cl->options, cl_ncurses))
		return ;
	printf(FTP_RESET"Server: "FTP_GREEN"%s"FTP_RESET"\n"
	"Client: "FTP_PINK"%s"FTP_RESET"\n"
	"%s > "FTP_RESET,
	cl->server.pwd, cl->pwd, (!cl->success) ? FTP_RED : FTP_GREEN);
	fflush(stdout);
}
