/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 18:18:08 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/03/17 16:09:06 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int				cl_ls(char *buf, char **cmd, t_client *cl)
{
	int			i;
	int			errnb;

	i = 1;
	(void)buf;
	ft_strcpy(cl->server.cmd, "LIST");
	while (cmd[i])
	{
		ft_strncat(cl->server.cmd, " ", CMD_BUFF_SIZE);
		ft_strncat(cl->server.cmd, cmd[i], CMD_BUFF_SIZE);
		i++;
	}
	ft_strncat(cl->server.cmd, "\n", CMD_BUFF_SIZE);
	if ((errnb = cl_server_write("PASV\n", &cl->server, cl)) != IS_OK)
		return (errnb);
	cl->server.receive_data = 1;
	cl->server.wait_response = 1;
	return (errnb);
}

int				cl_ls_help(t_command *cmd, t_client *cl)
{
	static char		*help[] = {
		"This command list the current directory filesystem or the",
		"file / directory as first argument.", NULL
	};

	return (cl_help_print(cmd, "[<file_name / directory_name>]", help, cl));
}
