/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_listen_from.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 02:47:15 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/10 19:02:45 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sv_main.h"

int					sv_listen_from(t_client *cl, t_server *sv)
{
	struct sockaddr	csin;
	socklen_t		len;

	ft_close(&cl->data.socket);
	len = sizeof(csin);
	if ((cl->data.socket = accept(cl->data.pasv_fd, &csin, &len)) < 0)
		return ((cl->version == sv_v4) ? ERR_ACCEPT_V4 : ERR_ACCEPT_V6);
	ft_close(&cl->data.pasv_fd);
	if (FT_CHECK(sv->options, sv_interactive))
		printf("Client "FTP_GREEN"%d"FTP_RESET": Connected to DATA port.\n",
		cl->fd);
	return (IS_OK);
}
