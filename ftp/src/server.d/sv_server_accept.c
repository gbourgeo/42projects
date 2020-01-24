/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_server_accept.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 05:44:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/21 16:03:26 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/select.h>
#include "sv_main.h"

static char		*sv_guest_home(t_user *us, t_server *sv)
{
	if (sv->options & (1 << sv_user_mode))
		while (us)
		{
			if (!ft_strcmp(us->name, SV_GUEST_NAME))
				return (us->home);
			else
				us = us->next;
		}
	return (sv->info.env.home);
}

static int		integrate_client(t_client *cl, t_server *sv)
{
	if ((cl->next = sv->clients))
		cl->next->prev = cl;
	sv->clients = cl;
	if (!cl->pwd || !cl->oldpwd)
		return (ERR_MALLOC);
	sv->connected++;
	if (FT_CHECK(sv->options, sv_interactive))
		printf("Client "FTP_YELLOW"%d"FTP_RESET": connected to %s.\n",
		cl->fd, cl->home);
	sv_welcome(cl, sv);
	return (IS_OK);
}

static int		accept_client(int version, int fd, t_server *sv)
{
	t_client	*cl;
	socklen_t	len;

	if (!(cl = ft_memalloc(sizeof(*cl))))
		return (ERR_MALLOC);
	cl->version = version;
	cl->fd = fd;
	cl->fct_read = sv_client_recv;
	cl->fct_write = sv_client_send;
	cl->rd.head = cl->rd.buff;
	cl->rd.tail = cl->rd.head;
	cl->rd.len = CMD_BUFF_SIZE;
	cl->wr.head = cl->wr.buff;
	cl->wr.tail = cl->wr.head;
	cl->home = sv_guest_home(sv->users, sv);
	cl->pwd = ft_strdup("/");
	cl->oldpwd = ft_strdup("/");
	len = sizeof(cl->sockaddr);
	getsockname(cl->fd, &cl->sockaddr, &len);
	cl->data.port = ft_itoa(ft_atoi(sv->port) - 1);
	cl->data.type = (1 << data_type_ascii);
	cl->data.byte_size = 8;
	cl->data.fd = -1;
	cl->login.member = sv_getuserbyname(sv->users, SV_GUEST_NAME);
	return (integrate_client(cl, sv));
}

int				sv_server_accept(int version, t_server *sv)
{
	int				fd;
	struct sockaddr	csin;
	socklen_t		len;

	len = sizeof(csin);
	if ((fd = accept(sv->ip[version], &csin, &len)) < 0)
		return ((version == sv_v4) ? ERR_ACCEPT_V4 : ERR_ACCEPT_V6);
	if (fd >= FD_SETSIZE)
	{
		send(fd, "Server Busy. Come back later !\n", 31, 0);
		close(fd);
		return (IS_OK);
	}
	if (sv->connected + 1 == CLIENTS_MAX)
	{
		send(fd, "Server Full. Come back later !\n", 31, 0);
		close(fd);
		return (IS_OK);
	}
	return (accept_client(version, fd, sv));
}
