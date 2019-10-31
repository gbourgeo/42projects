/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_server_accept.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 05:44:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/31 03:21:30 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sv_main.h"

static void		print_info_client(t_client *cl)
{
	ft_putstr("Client \x1B[33m");
	ft_putnbr(cl->fd);
	ft_putstr("\x1B[0m connected to \"\x1B[1;35m");
	ft_putstr(cl->home);
	ft_putendl("\x1B[0m\".");
}

static char		*sv_guest_home(t_user *us)
{
	while (us)
		if (!ft_strcmp(us->name, SV_GUEST_NAME))
			return (us->home);
		else
			us = us->next;
	return (NULL);
}

static int		accept_client(int version, int fd, t_server *sv)
{
	t_client	*cl;

	if (!(cl = ft_memalloc(sizeof(*cl))))
		return (ERR_MALLOC);
	cl->version = version;
	cl->fd = fd;
	cl->fct_read = sv_client_recv;
	cl->fct_write = sv_client_send;
	cl->rd.head = cl->rd.buff;
	cl->rd.tail = cl->rd.head;
	cl->rd.len = FTP_BUFF_SIZE;
	cl->wr.head = cl->wr.buff;
	cl->wr.tail = cl->wr.head;
	cl->wr.len = 0;
	cl->home = sv_guest_home(sv->users);
	cl->pwd = ft_strdup("/");
	cl->oldpwd = ft_strdup("/");
	if ((cl->next = sv->clients))
		cl->next->prev = cl;
	sv->clients = cl;
	if (!cl->pwd || !cl->oldpwd)
		return (ERR_MALLOC);
	if (sv->interactive)
		print_info_client(cl);
	return (IS_OK);
}

int				sv_server_accept(int version, t_server *sv)
{
	int				fd;
	struct sockaddr	csin;
	socklen_t		len;

	len = sizeof(csin);
	if ((fd = accept(sv->ip[version], &csin, &len)) < 0)
		return ((version == v4) ? ERR_ACCEPT_V4 : ERR_ACCEPT_V6);
	if (sv->connected + 1 == CLIENTS_MAX)
	{
		send(fd, "Server Full. Come back later !\n", 31, 0);
		close(fd);
		return (IS_OK);
	}
	sv->connected++;
	return (accept_client(version, fd, sv));
}
