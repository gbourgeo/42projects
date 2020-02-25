/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 18:15:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/24 17:58:33 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int				cl_cd(char *buf, char **cmd, t_client *cl)
{
	int		i;

	i = 1;
	ft_strcpy(buf, "CWD");
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

int				cl_cd_help(t_command *cmd, t_client *cl)
{
	static char		*help[] = {
		"This command allows the client to change the server",
		"working directory.", NULL
	};

	return (cl_help_print(cmd, "[<directory_name>]", help, cl));
}
