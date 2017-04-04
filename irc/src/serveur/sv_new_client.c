/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_new_client.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/26 17:26:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/04 02:21:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

static void			sv_init_buf(t_buf *info, char *buff, int len)
{
	info->start = &buff[0];
	info->end = &buff[BUFF + 1];
	info->head = &buff[0];
	info->tail = &buff[0];
	info->len = len;
}

static t_fd			*new_client_error(int fd, char *str, t_fd *cl, t_env *e)
{
	if (e->verb)
		ft_putendl(str);
	send(fd, str, ft_strlen(str), 0);
	close(fd);
	if (cl)
		free(cl);
	return (NULL);
}

/*
** If, in client_id(...), i == 3 we have all the unique user identity taken.
** Shall we accept new connection ? Seems not pretty legit...
*/

static void			client_uid(t_fd *cl, t_env *e)
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

static t_fd			*new_fd(int fd, struct sockaddr *csin, t_env *e)
{
	t_fd			*cl;

	if ((cl = (t_fd *)malloc(sizeof(*cl))) == NULL)
		return (new_client_error(fd, "ERROR :Malloc failed\r\n", cl, e));
	ft_memset(cl, 0, sizeof(*cl));
	cl->fd = fd;
	ft_memcpy(&cl->csin, csin, sizeof(cl->csin));
	client_uid(cl, e);
	if ((cl->inf = (t_file *)malloc(sizeof(*cl->inf))) == NULL)
		return (new_client_error(fd, "ERROR :Malloc failed\r\n", cl, e));
	ft_memset(cl->inf, 0, sizeof(*cl->inf));
	cl->type = FD_CLIENT;
	cl->time = time(NULL);
	cl->fct_read = sv_cl_read;
	cl->fct_write = sv_cl_send;
	sv_init_buf(&cl->rd, cl->buf_read, BUFF);
	sv_init_buf(&cl->wr, cl->buf_write, 0);
	sv_notice("Looking up your hostname...", cl, e);
	if (getnameinfo(&cl->csin, sizeof(cl->csin), cl->addr, NI_MAXHOST,
					cl->port, NI_MAXSERV, NI_NUMERICSERV))
		sv_notice("Couldn't look up your hostname", cl, e);
	return (cl);
}

void				sv_new_client(int fd, struct sockaddr *csin, t_env *e)
{
	t_fd			*cl;

	if ((cl = new_fd(fd, csin, e)) == NULL)
		return ;
	if (e->fds)
		e->fds->prev = cl;
	cl->next = e->fds;
	e->fds = cl;
	if (LOCK_SERVER)
		sv_notice("The server runs in registered-user only mode.", cl, e);
	if (e->verb)
		printf("\e[32mNew connection from\e[0m %s:%s\n", cl->addr, cl->port);
}
