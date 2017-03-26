/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_new_client.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 17:26:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/25 23:14:37 by gbourgeo         ###   ########.fr       */
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
	info->len = BUFF;
}

static void			new_client_error(int fd, char *str, t_env *e)
{
	if (e->verb)
		ft_putendl(str);
	send(fd, str, ft_strlen(str), 0);
	close(fd);
}

/*
** If, in client_id(...), i == 3 we have all the unique user identity taken.
** Shall we not accept new connection ? Seems pretty legit.
*/

static void			client_id(t_fd *cl, t_env *e)
{
	int				i;

	i = 8;
	ft_strcpy(cl->uid, e->userid);
	while (i > 3 && e->userid[i] == 'Z')
	{
		e->userid[i] = 'A';
		i--;
	}
	if (i > 3)
		e->userid[i] += 1;
}

void				sv_new_client(int fd, struct sockaddr *csin, t_env *e)
{
	t_fd			*cl;

	if ((cl = (t_fd *)malloc(sizeof(*cl))) == NULL)
		return (new_client_error(fd, "ERROR :Malloc failed\r\n", e));
	ft_memset(cl, 0, sizeof(*cl));
	cl->fd = fd;
	ft_memcpy(&cl->csin, csin, sizeof(cl->csin));
	sv_notice("Looking up your hostname...", cl, e);
	if (getnameinfo(&cl->csin, sizeof(cl->csin), cl->addr, NI_MAXHOST,
					cl->port, NI_MAXSERV, NI_NUMERICSERV))
		sv_notice("Couldn't look up your hostname", cl, e);
	client_id(cl, e);
	cl->type = FD_CLIENT;
	cl->time = time(NULL);
	cl->fct_read = sv_cl_read;
	sv_init_buf(&cl->rd, cl->buf_read);
	sv_init_buf(&cl->wr, cl->buf_write);
	if (e->fds)
		e->fds->prev = cl;
	cl->next = e->fds;
	e->fds = cl;
	if (LOCK_SERVER)
		sv_notice("The server runs in registered-user only mode", cl, e);
	if (e->verb)
		printf("\e[32mNew connection from\e[0m %s :%s\n", cl->addr, cl->port);
}
