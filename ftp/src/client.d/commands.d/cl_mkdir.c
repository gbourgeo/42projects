/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_mkdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 18:18:26 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/24 17:59:21 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int				cl_mkdir(char *buf, char **cmd, t_client *cl)
{
	int		i;

	i = 1;
	ft_strcpy(buf, "MKD");
	while (cmd[i])
	{
		ft_strncat(buf, " ", CMD_BUFF_SIZE);
		ft_strncat(buf, cmd[i], CMD_BUFF_SIZE);
		i++;
	}
	ft_strncat(buf, "\n", CMD_BUFF_SIZE);
	cl->precmd = cl_new_command("NLST", cl->ncu.slistwin,
	(char *[]){ "2", "22" }, cl->precmd);
	return (cl_server_write(buf, &cl->server, cl));
}

int				cl_mkdir_help(t_command *cmd, t_client *cl)
{
	static char		*help[] = {
		"This command creates a new directory specified as first",
		"argument to the command.", NULL
	};

	return (cl_help_print(cmd, "<directory_name>", help, cl));
}
