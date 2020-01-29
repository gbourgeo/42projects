/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_new_pid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:56:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/29 19:56:03 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sv_main.h"

static int		sv_preprocess(char **cmds, t_client *cl, int (*hdlr)())
{
	int			errnb;

	if (cl->data.port
	&& (errnb = sv_connect_to(&cl->data.socket, cl)) != IS_OK)
		return (errnb);
	return (hdlr(cmds, cl));
}

int				sv_new_pid(char **cmds, t_client *cl, int (*hdlr)())
{
	int			errnb;

	if (cl->data.pid > 0)
		return (sv_response(cl, "425 Service not available yet"));
	if (cl->data.pasv_fd > 0 && cl->data.socket < 0)
		return (sv_response(cl, "425 Connection not established"));
	cl->data.pid = fork();
	if (cl->data.pid < 0)
		return (ERR_FORK);
	if (cl->data.pid == 0)
	{
		errnb = sv_preprocess(cmds, cl, hdlr);
		ft_tabdel(&cmds);
		sv_server_end(&g_serv, 0);
		exit(errnb);
	}
	ft_strdel(&cl->data.port);
	ft_close(&cl->data.pasv_fd);
	return (IS_OK);
}
