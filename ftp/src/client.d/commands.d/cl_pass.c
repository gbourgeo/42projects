/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_pass.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 17:24:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/03/18 09:10:48 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int					cl_pass(char *buf, char **cmd, t_client *cl)
{
	ft_strcpy(buf, "PASS");
	ft_strncat(buf, " ", CMD_BUFF_SIZE);
	ft_strncat(buf, cmd[1], CMD_BUFF_SIZE);
	ft_strncat(buf, "\n", CMD_BUFF_SIZE);
	cl->precmd = cl_new_command("NLST", cl->ncu.slistwin,
	(char *[]){ "2", "22" }, cl->precmd);
	return (cl_server_write(buf, &cl->server, cl));
}

int					cl_pass_help(t_command *cmd, t_client *cl)
{
	static char		*help[] = {
		"This command sends to the server the password needed to log in",
		"if the server needs it. This command MUST be preceded by the ",
		"command USER.", NULL
	};

	return (cl_help_print(cmd, "<password>", help, cl));
}
