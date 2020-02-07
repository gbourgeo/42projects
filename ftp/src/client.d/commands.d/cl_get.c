/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 18:17:26 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/07 20:40:15 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

static int		cl_get_end(t_server *sv)
{
	ft_close(&sv->fd_data);
	sv->receive_data = 0;
	sv->wait_response = 0;
	ft_bzero(sv->response, sizeof(sv->response));
	ft_bzero(sv->cmd, sizeof(sv->cmd));
	sv->fct = NULL;
	return (IS_OK);
}

int				cl_get(char *buf, char **cmd, t_client *cl)
{
	int			i;
	int			errnb;

	i = 1;
	(void)buf;
	ft_strcpy(cl->server.cmd, "RETR");
	while (cmd[i])
	{
		ft_strncat(cl->server.cmd, " ", CMD_BUFF_SIZE);
		ft_strncat(cl->server.cmd, cmd[i], CMD_BUFF_SIZE);
		i++;
	}
	ft_strncat(cl->server.cmd, "\n", CMD_BUFF_SIZE);
	if ((errnb = cl_server_write("PASV\n", 5, &cl->server, cl)) != IS_OK)
		return (errnb);
	cl->server.receive_data = 1;
	cl->server.wait_response = 1;
	cl->server.fct = cl_get_end;
	return (errnb);
}

int					cl_get_help(t_command *cmd, t_client *cl)
{
	static char		*help[] = {
		"", NULL
	};

	return (cl_help_print(cmd, help, cl));
}
