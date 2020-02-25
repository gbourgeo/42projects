/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 18:19:02 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/24 17:59:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int				cl_pwd(char *buf, char **cmd, t_client *cl)
{
	int		i;

	i = 1;
	ft_strcpy(buf, "PWD");
	while (cmd[i])
	{
		ft_strncat(buf, " ", CMD_BUFF_SIZE);
		ft_strncat(buf, cmd[i], CMD_BUFF_SIZE);
		i++;
	}
	ft_strncat(buf, "\n", CMD_BUFF_SIZE);
	return (cl_server_write(buf, &cl->server, cl));
}

int				cl_pwd_help(t_command *cmd, t_client *cl)
{
	static char		*help[] = {
		"This command prints the current working directory on the",
		"server.", NULL
	};

	return (cl_help_print(cmd, "", help, cl));
}
