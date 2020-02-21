/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_new_pid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:56:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/21 15:28:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sv_main.h"

static int	sv_preprocess(char **cmds, t_client *cl, char *opt)
{
	int			errnb;

	if (cl->data.port
	&& (errnb = sv_connect_to(&cl->data.socket, cl)) != IS_OK)
		return (errnb);
	return (cl->data.function(opt, cmds, cl));
}

int			sv_new_pid(char **cmds, t_client *cl, char *opt)
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
		errnb = sv_preprocess(cmds, cl, opt);
		ft_tabdel(&cmds);
		sv_server_end(&g_serv, 0);
		exit(errnb);
	}
	if (FT_CHECK(g_serv.options, sv_interactive))
		printf("Client "FTP_GREEN"%d"FTP_RESET": DATA transfert started...\n",
		cl->fd);
	sv_free_data(&cl->data);
	return (IS_OK);
}
