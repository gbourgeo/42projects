/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_server_accept.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 05:44:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/26 17:56:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
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
	if (SV_CHECK(sv->options, sv_interactive))
		printf("Client "COLOR_YELLOW"%d"COLOR_RESET": connected to %s.\n",
		cl->fd, cl->home);
	if (SV_CHECK(sv->options, sv_user_mode))
		cl->errnb[0] = sv_client_write("You must signin to connect...\n", cl);
	return (IS_OK);
}

static int		accept_client(int version, int fd, t_server *sv)
{
	t_client	*cl;
	t_user		*user;

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
	cl->wr.len = 0;
	cl->home = sv_guest_home(sv->users, sv);
	cl->pwd = ft_strdup("/");
	cl->oldpwd = ft_strdup("/");
	cl->data.fd = -1;
	user = sv_getuserbyname(sv->users, SV_GUEST_NAME);
	if (SV_CHECK(sv->options, sv_user_mode))
		cl->user = (user) ? *user : (t_user){ 0 };
	else
		cl->user.rights = 3;
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
	if (sv->connected + 1 == CLIENTS_MAX)
	{
		send(fd, "Server Full. Come back later !\n", 31, 0);
		close(fd);
		return (IS_OK);
	}
	return (accept_client(version, fd, sv));
}
