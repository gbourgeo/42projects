/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 18:17:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/24 17:59:01 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int				cl_help(char *buf, char **cmd, t_client *cl)
{
	int			i;

	i = 1;
	ft_strcpy(buf, "HELP");
	while (cmd[i])
	{
		ft_strncat(buf, " ", CMD_BUFF_SIZE);
		ft_strncat(buf, cmd[i], CMD_BUFF_SIZE);
		i++;
	}
	ft_strncat(buf, "\n", CMD_BUFF_SIZE);
	return (cl_server_write(buf, &cl->server, cl));
}

int				cl_help_help(t_command *cmd, t_client *cl)
{
	static char		*help[] = {
		"This command print the server help.", NULL
	};

	return (cl_help_print(cmd, "[<command_name>]", help, cl));
}
