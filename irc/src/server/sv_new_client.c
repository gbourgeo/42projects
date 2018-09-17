/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_new_client.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 17:26:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/11 08:32:34 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

static void			sv_init_buf(t_buf *info, char *buff, int len)
{
	info->start = &buff[0];
	info->end = &buff[BUFF + 1];
	info->head = &buff[0];
	info->tail = &buff[0];
	info->len = len;
}

/*
** If, in client_id(...), i == 3 we have all the unique user identity taken.
** Shall we accept new connection ? Seems not pretty legit...
*/

static void			client_uid(t_fd *cl)
{
	int				i;

	i = 8;
	ft_strcpy(cl->uid, e.userid);
	while (i > 3 && e.userid[i] == 'Z')
	{
		e.userid[i] = 'A';
		i--;
	}
	if (i > 3)
		e.userid[i] += 1;
}

void				sv_new_client(t_info *info)
{
	t_fd			*cl;

	if ((cl = (t_fd *)malloc(sizeof(*cl))) == NULL)
		sv_error("ERROR :Malloc (t_fd) failed.", &e);
	ft_memset(cl, 0, sizeof(*cl));
	ft_memcpy(&cl->i, info, sizeof(*info));
	client_uid(cl);
	if ((cl->inf = (t_file *)malloc(sizeof(*cl->inf))) == NULL)
		sv_error("ERROR :Malloc failed\r\n", &e);
	ft_memset(cl->inf, 0, sizeof(*cl->inf));
	cl->type = FD_CLIENT;
	cl->fct_read = sv_cl_read;
	cl->fct_write = sv_cl_send;
	sv_init_buf(&cl->rd, cl->buf_read, BUFF);
	sv_init_buf(&cl->wr, cl->buf_write, 0);
	if (e.fds)
		e.fds->prev = cl;
	cl->next = e.fds;
	e.fds = cl;
	if (e.verb)
		printf("Connection %s(%s):%s\n", cl->i.addr, cl->i.host, cl->i.port);
}
