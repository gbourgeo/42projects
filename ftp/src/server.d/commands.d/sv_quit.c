/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_quit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 15:46:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/18 20:23:28 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int			sv_quit(char **cmds, t_client *cl, t_server *sv)
{
	if (cmds[1])
		return (sv_cmd_err("too much parameters", cmds[0], cl, sv));
	return (ERR_DISCONNECT);
}

int				sv_quit_help(t_command *cmd, t_client *cl)
{
	int		errnb;

	if ((errnb = sv_client_write(cmd->name, cl)) == IS_OK
	&& (errnb = sv_client_write(": Quit the server\n", cl)) == IS_OK)
		errnb = sv_client_write("\n", cl);
	return (errnb);
}
