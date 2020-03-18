/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_nlst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 02:56:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/03/17 16:08:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int				cl_nlst(char *buf, char **cmd, t_client *cl)
{
	int			i;
	int			errnb;

	i = 1;
	(void)buf;
	ft_strcpy(cl->server.cmd, "NLST");
	if (cmd)
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
	cl->server.wait_response = 2;
	return (errnb);
}

int				cl_nlst_help(t_command *cmd, t_client *cl)
{
	static char		*help[] = {
		"This command prints a short listing of the current directory or",
		"the file / directory pointed as first argument on the server.",
		" This command is usefull for a complete get or put of a",
		"directory.", NULL
	};

	return (cl_help_print(cmd, "[<file_name / directory_name>]", help, cl));
}
