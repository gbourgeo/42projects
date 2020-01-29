/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_client_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:00:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/29 16:51:34 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int				sv_client_init(t_client *cl, t_server *sv)
{
	socklen_t	len;

	cl->fct_read = sv_client_recv;
	cl->fct_write = sv_client_send;
	cl->rd.head = cl->rd.buff;
	cl->rd.tail = cl->rd.head;
	cl->rd.len = CMD_BUFF_SIZE;
	cl->wr.head = cl->wr.buff;
	cl->wr.tail = cl->wr.head;
	cl->home = sv_guest_home(sv->users, sv);
	if (!(cl->pwd = ft_strdup("/")) || !(cl->oldpwd = ft_strdup("/")))
		return (ERR_MALLOC);
	len = sizeof(cl->sockaddr);
	getsockname(cl->fd, &cl->sockaddr, &len);
	cl->data.type = (1 << data_type_ascii);
	cl->data.byte_size = 8;
	cl->data.pasv_fd = -1;
	cl->data.socket = -1;
	cl->login.member = sv_getuserbyname(sv->users, SV_GUEST_NAME);
	return (IS_OK);
}
