/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_client_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/26 16:58:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/03/18 13:47:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

static int		cl_client_exec_cmd(char **cmd, t_client *cl)
{
	t_command	*cmds;
	long		i;

	cmds = cl_commands(0);
	i = 0;
	if (*cl->server.cmd == '\\')
		return (cl_bslash(cmd, cl));
	while (i < (long)cl_commands(1))
	{
		if (!ftp_strcmp(cmds[i].name, cmd[0]))
			return (cmds[i].func(cl->server.cmd, cmd, cl));
		i++;
	}
	return (cl_server_write(cl->server.cmd, &cl->server, cl));
}

int				cl_client_commands(t_buff *ring, t_client *cl)
{
	char		**cmd;
	int			errnb;

	ft_ringbuffcpy(cl->server.cmd, sizeof(cl->server.cmd) - 2, ring);
	ft_strncat(cl->server.cmd, "\n", 2);
	wprintw(cl->ncu.chatwin, "> %s", cl->server.cmd);
	wrefresh(cl->ncu.chatwin);
	if (!(cmd = ft_split_whitespaces(cl->server.cmd)))
		return (ERR_MALLOC);
	errnb = IS_OK;
	if (cmd[0] && cmd[0][0])
		errnb = cl_client_exec_cmd(cmd, cl);
	ft_tabdel(&cmd);
	ft_strclr(cl->server.response);
	return (errnb);
}
