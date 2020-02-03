/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_client_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 08:44:55 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/03 17:30:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/select.h>
#include <unistd.h>
#include <term.h>
#include "cl_main.h"

static int			client_init(t_client *cl)
{
	if (!(cl->server.pwd = ft_strdup("/")))
		return (ERR_MALLOC);
	if (!(cl->pwd = getcwd(NULL, 0)))
		return (ERR_MALLOC);
	cl->success = 1;
	cl->rd.head = cl->rd.buff;
	cl->rd.tail = cl->rd.buff;
	cl->wr.head = cl->wr.buff;
	cl->wr.tail = cl->wr.buff;
	cl->wr.len = sizeof(cl->wr.buff);
	cl->server.wr.head = cl->server.wr.buff;
	cl->server.wr.tail = cl->server.wr.buff;
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
	}
	if (cl->server.fd_ctrl > max)
		max = cl->server.fd_ctrl;
	return (max);
}

static void			check_fdset(fd_set *r, fd_set *w, int ret, t_client *cl)
{
	if (FD_ISSET(STDIN_FILENO, r) && ret-- > 0)
		cl->errnb[0] = cl_ncurses_read(&cl->rd, cl);
	if (FD_ISSET(STDIN_FILENO, w) && ret-- > 0)
		cl->errnb[1] = cl_ncurses_write(&cl->wr, cl);
	if (cl->server.fd_ctrl > 0 && ret > 0)
	{
		if (FD_ISSET(cl->server.fd_ctrl, r) && ret-- > 0)
			cl->errnb[2] = cl_server_recv(&cl->wr, &cl->server, cl);
		if (FD_ISSET(cl->server.fd_ctrl, w) && ret-- > 0)
			cl->errnb[3] = cl_server_send(cl->server.fd_ctrl, &cl->server.wr);
	}
	// if (cl->server.fd_data > 0 && cl->server.get_data)
	// {
	// 	if (FD_ISSET(cl->server.fd_data, r))
	// 		cl->errnb[1] = cl_server_recv_data(cl);
		// if (FD_ISSET(cl->server.fd_data, w))
		// 	cl->errnb[2] = cl_server_send(cl);
	// }
}

static int			check_errors(t_client *cl)
{
	unsigned long		i;

	i = 0;
	while (i++ < sizeof(cl->errnb) / sizeof(cl->errnb[0]))
		// if (cl->errnb[i] == ERR_DISCONNECT)
		// 	return (ERR_DISCONNECT);
		// else
		if (cl->errnb[i - 1] != IS_OK)
		{
			wattron(cl->ncu.chatwin, COLOR_PAIR(CL_RED));
			wprintw(cl->ncu.chatwin, "**ERROR: ");
			wattron(cl->ncu.chatwin, COLOR_PAIR(CL_BLUE));
			wprintw(cl->ncu.chatwin, "%s\n", ft_get_error(cl->errnb[i - 1]));
			wattroff(cl->ncu.chatwin, COLOR_PAIR(CL_BLUE));
			wrefresh(cl->ncu.chatwin);
			if (cl->errnb[i - 1] == ERR_DISCONNECT)
				ft_close(&cl->server.fd_ctrl);
			cl->errnb[i - 1] = IS_OK;
		}
	return (IS_OK);
}

int					cl_client_loop(t_client *cl)
{
	struct timeval	timeout;
	fd_set			fds[2];
	int				max;
	int				ret;

	cl->errnb[0] = cl_get_addrinfo(cl);
	cl->errnb[1] = client_init(cl);
	timeout.tv_sec = 0;
	timeout.tv_usec = 0;
	while (check_errors(cl) == IS_OK)
	{
		wrefresh(cl->ncu.textwin);
		max = init_fdset(&fds[0], &fds[1], cl);
		ret = select(max + 1, &fds[0], &fds[1], NULL, &timeout);
		if (ret < 0)
			return (ERR_SELECT);
		if (ret > 0)
			check_fdset(&fds[0], &fds[1], ret, cl);
	}
	return (ERR_DISCONNECT);
}
