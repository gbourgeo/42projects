/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_client_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/26 16:58:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/17 06:22:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

static int		cl_client_exec_cmd(char *buf, char **cmd, t_client *cl)
{
	t_command	*cmds;
	long		i;

	cmds = cl_commands(0);
	i = 0;
	if (*buf == '\\')
		return (cl_bslash(cmd, cl));
	while (i < (long)cl_commands(1))
	{
		if (!ftp_strcmp(cmds[i].name, cmd[0]))
			return (cmds[i].func(buf, cmd, cl));
		i++;
	}
	return (cl_server_write(buf, ft_strlen(buf), &cl->server, cl));
}

int				cl_client_commands(t_buff *ring, t_client *cl)
{
	char		buff[CMD_BUFF_SIZE + 1];
	char		**cmd;
	int			errnb;

	ft_ringbuffcpy(buff, sizeof(buff), ring);
	ft_strcat(buff, "\n");
	if (!(cmd = ft_split_whitespaces(buff)))
		return (ERR_MALLOC);
	errnb = IS_OK;
	if (cmd[0] && cmd[0][0])
		errnb = cl_client_exec_cmd(buff, cmd, cl);
	ft_tabdel(&cmd);
	return (errnb);
}
