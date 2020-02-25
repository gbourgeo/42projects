/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_client_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 08:44:55 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/24 14:24:45 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/select.h>
#include <unistd.h>
#include <term.h>
#include "cl_main.h"
#include "cl_struct.h"

static int			cl_client_init(t_client *cl)
{
	cl->printtowin = cl->ncu.chatwin;
	cl->rd.head = cl->rd.buff;
	cl->rd.tail = cl->rd.buff;
	cl->rd.len = 0;
	cl->wr.head = cl->wr.buff;
	cl->wr.tail = cl->wr.buff;
	cl->wr.len = sizeof(cl->wr.buff);
	cl->server.fd_data = -1;
	cl->server.receive_data = -1;
	cl->server.wait_response = 0;
	cl->server.filename = NULL;
	cl->server.filefd = -1;
	cl->server.ret = 0;
	cl->server.wr.head = cl->server.wr.buff;
	cl->server.wr.tail = cl->server.wr.buff;
	cl->server.wr.len = 0;
	ft_bzero(cl->server.cmd, sizeof(cl->server.cmd));
	ft_bzero(cl->server.response, sizeof(cl->server.response));
	return (IS_OK);
}

static int			init_fdset(fd_set *r, fd_set *w, t_client *cl)
{
	int		max;

	max = 0;
	FD_ZERO(r);
	FD_ZERO(w);
	FD_SET(STDIN_FILENO, r);
	FD_SET(STDIN_FILENO, w);
	if (cl->server.fd_ctrl > 0)
	{
		FD_SET(cl->server.fd_ctrl, r);
		FD_SET(cl->server.fd_ctrl, w);
		if (cl->server.fd_ctrl > max)
			max = cl->server.fd_ctrl;
	}
	if (cl->server.fd_data > 0)
	{
		if (cl->server.receive_data)
			FD_SET(cl->server.fd_data, r);
		else
			FD_SET(cl->server.fd_data, w);
		if (cl->server.fd_data > max)
			max = cl->server.fd_data;
	}
	return (max);
}

static void			check_fdset(fd_set *r, fd_set *w, t_client *cl)
{
	if (FD_ISSET(STDIN_FILENO, r))
		cl->errnb[0] = cl_ncurses_read(&cl->rd, cl);
	if (FD_ISSET(STDIN_FILENO, w))
		cl->errnb[1] = cl_ncurses_write(&cl->wr, cl);
	if (cl->server.fd_ctrl > 0)
	{
		if (FD_ISSET(cl->server.fd_ctrl, r))
			cl->errnb[2] = cl_server_recv(&cl->wr, cl->server.fd_ctrl, cl);
		if (FD_ISSET(cl->server.fd_ctrl, w))
			cl->errnb[3] = cl_server_send(&cl->server.wr, cl->server.fd_ctrl,
			cl);
		if (cl->server.wait_response > 0)
			cl->errnb[4] = cl_response(&cl->server, cl);
	}
	if (cl->server.fd_data > 0)
	{
		if (cl->server.receive_data > 0 && FD_ISSET(cl->server.fd_data, r))
			cl->errnb[5] = cl_server_recv_data(&cl->server, cl);
		if (cl->server.receive_data == 0 && FD_ISSET(cl->server.fd_data, w))
			cl->errnb[6] = cl_server_send_data(&cl->server, cl);
	}
}

static int			check_errors(t_client *cl)
{
	int		i;

	i = -1;
	while (++i < (int)(sizeof(cl->errnb) / sizeof(cl->errnb[0])))
		if (cl->errnb[i] == ERR_QUIT)
			return (ERR_QUIT);
		else if (cl->errnb[i] != IS_OK)
		{
			ft_strcpy(cl->server.response, "500 Error\n");
			wattron(cl->ncu.chatwin, COLOR_PAIR(CL_RED));
			wprintw(cl->ncu.chatwin, "**ERROR**: ");
			wattron(cl->ncu.chatwin, COLOR_PAIR(CL_BLUE));
			wprintw(cl->ncu.chatwin, "%s\n", ft_get_error(cl->errnb[i]));
			wattroff(cl->ncu.chatwin, COLOR_PAIR(CL_BLUE));
			wrefresh(cl->ncu.chatwin);
			if (cl->errnb[i] == ERR_DISCONNECT)
				cl_server_close(&cl->server, cl);
			cl->errnb[i] = IS_OK;
		}
	if (cl->server.ret < 0)
		cl_server_close_data(&cl->server);
	return (IS_OK);
}

int					cl_client_loop(t_client *cl)
{
	struct timeval	timeout;
	fd_set			fds[2];
	int				max;
	int				ret;

	cl->verbose = 1;
	cl->errnb[0] = cl_get_userinfo(&cl->server, cl);
	cl->errnb[1] = cl_get_addrinfo(&cl->server.fd_ctrl, cl->addr, cl->port, cl);
	cl->errnb[2] = cl_client_init(cl);
	cl->errnb[3] = cl_pre_command(&cl->precmd, &cl->server, cl);
	cl->verbose = FT_CHECK(cl->options, cl_verbose);
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	while (check_errors(cl) == IS_OK)
	{
		cl->precmd = cl_pre_cmd_exec(cl->precmd, &cl->server, cl);
		wrefresh(cl->ncu.textwin);
		max = init_fdset(&fds[0], &fds[1], cl);
		ret = select(max + 1, &fds[0], &fds[1], NULL, &timeout);
		if (ret < 0)
			return (ERR_SELECT);
		if (ret > 0)
			check_fdset(&fds[0], &fds[1], cl);
	}
	return (ERR_QUIT);
}
