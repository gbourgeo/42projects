/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_client_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 08:44:55 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/10 18:00:59 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/select.h>
#include <unistd.h>
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
	if (cl->rd.len < CMD_BUFF_SIZE)
		FD_SET(STDIN_FILENO, r);
	if (cl->server.fd > 0)
		FD_SET(cl->server.fd, r);
	if (cl->server.fd > max)
		max = cl->server.fd;
	return (max);
}

static int			check_fdset(fd_set *r, fd_set *w, t_client *cl)
{
	if (FD_ISSET(STDIN_FILENO, r))
		return ((FT_CHECK(cl->options, cl_ncurses))
		? cl_ncurses_read(cl) : cl_stdin_read(cl));
	else if (FD_ISSET(cl->server.fd, r))
		return (cl_server_recv(cl));
	else if (FD_ISSET(cl->server.fd, w))
		return (cl_server_send(cl));
	return (IS_OK);
}

int					cl_client_loop(t_client *cl)
{
	int				max;
	int				ret;
	fd_set			fds[2];
	struct timeval	timeout;
	int				errnb;

	if ((errnb = client_info(cl)) != IS_OK)
		return (errnb);
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	cl_prompt(cl);
	while (errnb == IS_OK)
	{
		max = init_fdset(&fds[0], &fds[1], cl);
		ret = select(max + 1, &fds[0], &fds[1], NULL, &timeout);
		if (ret < 0)
			return (ERR_SELECT);
		if (ret > 0)
			errnb = check_fdset(&fds[0], &fds[1], cl);
	}
	return (errnb);
}

void				cl_prompt(t_client *cl)
{
	if (FT_CHECK(cl->options, cl_ncurses))
		return ;
	printf(FTP_RESET"Server: "FTP_GREEN"%s"FTP_RESET"\n"
	"Client: "FTP_PINK"%s"FTP_RESET"\n"
	"%s > "FTP_RESET,
	cl->server.pwd, cl->pwd, (!cl->success) ? FTP_RED : FTP_GREEN);
	fflush(stdout);
}
