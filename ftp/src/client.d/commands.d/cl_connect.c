/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_connect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 02:24:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/17 04:11:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int					cl_connect(char *buf, char **cmd, t_client *cl)
{
	(void)buf;
	if (!cmd[1] || !cmd[2])
		return (ERR_NB_PARAMS);
	if (cl->server.fd_ctrl > 0)
		return (ERR_ALREADY_CONNECTED);
	return (cl_get_addrinfo(&cl->server.fd_ctrl, cmd[1], cmd[2], cl));
}

int					cl_connect_help(t_command *cmd, t_client *cl)
{
	static char		*help[] = {
		"This command allows the client to connect to a server",
		"remotly.", NULL
	};

	return (cl_help_print(cmd, "<address> <port>", help, cl));
}
