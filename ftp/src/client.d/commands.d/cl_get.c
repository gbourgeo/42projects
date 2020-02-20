/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 18:17:26 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/20 01:25:44 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

int				cl_get(char *buf, char **cmd, t_client *cl)
{
	int			i;
	int			errnb;

	(void)buf;
	i = 1;
	ft_strcpy(cl->server.cmd, "RETR");
	while (cmd[i])
	{
		ft_strncat(cl->server.cmd, " ", sizeof(cl->server.cmd) - 1);
		ft_strncat(cl->server.cmd, cmd[i], sizeof(cl->server.cmd) - 1);
		i++;
	}
	ft_strncat(cl->server.cmd, "\n", sizeof(cl->server.cmd) - 1);
	if ((errnb = cl_server_write("PASV\n", 5, &cl->server, cl)) != IS_OK)
		return (errnb);
	cl->server.receive_data = 1;
	cl->server.wait_response = 2;
	cl->server.filename = ft_strdup(cmd[1]);
	// cl->precmd = cl_new_command("\\ls -p", cl->ncu.clistwin, "212", "",
	// cl->precmd);
	return (errnb);
}

int				cl_get_help(t_command *cmd, t_client *cl)
{
	static char		*help[] = {
		"This command allows the user to receive a file from the server.",
		NULL
	};

	return (cl_help_print(cmd, "<filename / filepath>", help, cl));
}
