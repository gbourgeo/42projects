/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_client_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 15:00:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/03/17 13:28:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

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
	cl->home = sv_client_home(SV_GUEST_NAME, sv->users, sv);
	if (!(cl->pwd = ft_strdup("/"))
	|| !(cl->oldpwd = ft_strdup("/")))
		return (ERR_MALLOC);
	len = sizeof(cl->sockaddr);
	getsockname(cl->fd, &cl->sockaddr, &len);
	cl->data.type = (1 << data_type_ascii);
	cl->data.byte_size = 8;
	cl->data.pasv_fd = -1;
	cl->data.socket = -1;
	cl->login.member = sv_getuserbyname(sv->users, SV_GUEST_NAME);
	cl->login.logged = 0;
	return (IS_OK);
}
