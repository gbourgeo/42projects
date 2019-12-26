/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_data_accept.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/22 02:47:15 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/26 01:31:22 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sv_main.h"

int				sv_data_accept(t_client *cl, t_server *sv)
{
	struct sockaddr	csin;
	socklen_t		len;
	int				errnb;

	len = sizeof(csin);
	if ((cl->data.socket = accept(cl->data.fd, &csin, &len)) < 0)
		return ((cl->version == sv_v4) ? ERR_ACCEPT_V4 : ERR_ACCEPT_V6);
	cl->data.pid = fork();
	if (cl->data.pid < 0)
		return (ERR_FORK);
	if (cl->data.pid == 0)
	{
		errnb = cl->data.function(cl, sv);
		sv_server_end(sv, 0);
		exit(errnb);
	}
	ft_strdel(&cl->data.file);
	close(cl->data.fd);
	cl->data.fd = -1;
	close(cl->data.socket);
	cl->data.socket = -1;
	return (IS_OK);
}
