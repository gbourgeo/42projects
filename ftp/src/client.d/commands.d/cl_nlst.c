/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_nlst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 02:56:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/09 03:29:21 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int				cl_nlst(char *buf, char **cmd, t_client *cl)
{
	int			i;
	int			errnb;

	i = 1;
	(void)buf;
	ft_strcpy(cl->server.cmd, "NLST\n");
	if (cmd)
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
	return (errnb);
}

int				cl_nlst_help(t_command *cmd, t_client *cl)
{
	static char		*help[] = {
		"", NULL
	};

	return (cl_help_print(cmd, help, cl));
}
