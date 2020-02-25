/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_rmdir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 19:15:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/24 18:00:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int				cl_rmdir(char *buf, char **cmd, t_client *cl)
{
	int		i;

	i = 1;
	ft_strcpy(buf, "RMD");
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

int				cl_rmdir_help(t_command *cmd, t_client *cl)
{
	static char		*help[] = {
		"This command allows the user to erase a directory in the server.",
		NULL
	};

	return (cl_help_print(cmd, "<directory_name>", help, cl));
}
