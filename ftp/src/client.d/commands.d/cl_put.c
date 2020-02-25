/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 18:18:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/24 17:59:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "cl_main.h"

static int		cl_put_open_file(char *filepath, t_server *sv, t_env *env)
{
	int			errnb;

	ft_close(&sv->filefd);
	if (!(sv->filename = ft_strdup(filepath)))
		return (ERR_MALLOC);
	if ((errnb = ft_check_path(&sv->filename, env->pwd, "/")) == IS_OK)
	{
		if ((sv->filefd = open(sv->filename, O_RDONLY)) < 0)
			errnb = ERR_OPEN;
	}
	ft_strdel(&sv->filename);
	return (errnb);
}

int				cl_put(char *buf, char **cmd, t_client *cl)
{
	char		*ptr;
	int			errnb;

	(void)buf;
	if ((errnb = cl_put_open_file(cmd[1], &cl->server, &cl->info.env)))
		return (errnb);
	ft_strcpy(cl->server.cmd, "STOR ");
	if (cmd[1])
	{
		if ((ptr = ft_strrchr(cmd[1], '/')) == NULL)
			ptr = cmd[1];
		ft_strncat(cl->server.cmd, ptr, sizeof(cl->server.cmd) - 1);
	}
	ft_strncat(cl->server.cmd, "\n", sizeof(cl->server.cmd) - 1);
	if ((errnb = cl_server_write("PASV\n", &cl->server, cl)) != IS_OK)
		return (errnb);
	cl->server.receive_data = 0;
	cl->server.wait_response = 2;
	cl->precmd = cl_new_command("NLST", cl->ncu.slistwin,
	(char *[]){ "212", "22" }, cl->precmd);
	return (errnb);
}

int				cl_put_help(t_command *cmd, t_client *cl)
{
	static char		*help[] = {
		"This command allows the user to send a file to the server.", NULL
	};

	return (cl_help_print(cmd, "[<file_name / file_path>]", help, cl));
}
