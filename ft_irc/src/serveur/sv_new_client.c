/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_new_client.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 17:26:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/12 06:46:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

void				sv_welcome(t_env *e, t_fd *cl)
{
	send(cl->fd, ":Welcome to the Internet Relay Chat ", 36, 0);
	send(cl->fd, cl->nick, NICK_LEN, 0);
	send(cl->fd, "\n:Your host is ", 15, 0);
	send(cl->fd, e->name, NICK_LEN, 0);
	send(cl->fd, "\n:This server was created ", 26, 0);
	send(cl->fd, e->creation, ft_strlen(e->creation), 0);
	send(cl->fd, "\r\n", 2, 0);
}

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

static void			send_notice(int fd, char *str, t_env *e)
{
	send(fd, e->name, SERVER_LEN, 0);
	send(fd, " NOTICE * :*** ", 15, 0);
	send(fd, str, ft_strlen(str), 0);
	send(fd, END_CHECK, END_CHECK_LEN, 0);
}

void				sv_new_client(int fd, struct sockaddr *csin, t_env *e)
{
	t_fd			*cl;

	if ((cl = (t_fd *)malloc(sizeof(*cl))) == NULL)
		return (new_client_error(fd, "ERROR :Malloc failed", e));
	cl->fd = fd;
	ft_memcpy(&cl->csin, csin, sizeof(cl->csin));
	send_notice(fd, "Looking up your hostname...", e);
	if (getnameinfo(&cl->csin, sizeof(cl->csin), cl->addr, NI_MAXHOST,
					cl->port, NI_MAXSERV, NI_NUMERICSERV))
		send_notice(fd, "Couldn't look up your hostname", e);
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
	e->members++;
	if (e->verb)
		printf("\e[32mNew client from\e[0m %s :%s\n", cl->addr, cl->port);
/* 	if (!LOCK_SERVER) */
/* 		return (sv_connect_client(cl)); */
/* 	send(cl->fd, "Username: ", 10, 0); */
}
