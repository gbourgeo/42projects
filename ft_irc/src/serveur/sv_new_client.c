/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_new_client.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 17:26:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/13 06:17:10 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

static void			sv_init_buf(t_buf *info, char *buff)
{
	info->start = &buff[0];
	info->end = &buff[BUFF];
	info->head = &buff[0];
	info->tail = &buff[0];
	info->len = 0;
}

static void			new_client_error(int fd, char *str, t_env *e)
{
	if (e->verb)
		ft_putendl(str);
	send(fd, str, ft_strlen(str), 0);
	send(fd, END_CHECK, END_CHECK_LEN, 0);
	close(fd);
}

void				sv_new_client(int fd, struct sockaddr *csin, t_env *e)
{
	t_fd			*cl;

	if ((cl = (t_fd *)malloc(sizeof(*cl))) == NULL)
		return (new_client_error(fd, "ERROR :Malloc failed", e));
	cl->fd = fd;
	ft_memcpy(&cl->csin, csin, sizeof(cl->csin));
	sv_notice(fd, "Looking up your hostname...", e);
	if (getnameinfo(&cl->csin, sizeof(cl->csin), cl->addr, NI_MAXHOST,
					cl->port, NI_MAXSERV, NI_NUMERICSERV))
		sv_notice(fd, "Couldn't look up your hostname", e);
//	send_notice(fd, "Checking Ident", e);
//
//	send_notice(fd, "No Ident response", e);
	cl->type = FD_CLIENT;
	cl->time = time(NULL);
	cl->fct_read = sv_cl_read;
	cl->fct_write = sv_cl_write;
	sv_init_buf(&cl->rd, cl->buf_read);
	sv_init_buf(&cl->wr, cl->buf_write);
	cl->user = sv_new_user(cl);
	if (e->fds)
		e->fds->prev = cl;
	cl->next = e->fds;
	e->fds = cl;
	if (LOCK_SERVER)
	{
		send(cl->fd, "This server is protected. Please login.\r\n", 41, 0);
		send(cl->fd, "Username: ", 10, 0);
	}
	if (e->verb)
		printf("\e[32mNew connection from\e[0m %s :%s\n", cl->addr, cl->port);
/* 	send(cl->fd, "Username: ", 10, 0); */
}
