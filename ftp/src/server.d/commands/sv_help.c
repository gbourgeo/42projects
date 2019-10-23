/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:31:05 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/23 16:39:03 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int					sv_help(char **cmds, t_client *cl, t_server *sv)
{
	t_command		*cmd;
	int				ret;

	cmd = (t_command *)cmds;
	ret = IS_OK;
	if ((ret = sv_client_write(sv->info.progname, cl)) == IS_OK)
		if ((ret = sv_client_write(": -- help\n", cl)) == IS_OK)
			while (cmd && cmd->name && ret == IS_OK)
			{
				if ((ret = sv_client_write(cmd->name, cl)) == IS_OK)
					if ((ret = sv_client_write("\t\t", cl)) == IS_OK)
						if ((ret = sv_client_write(cmd->descrip, cl)) == IS_OK)
							ret = sv_client_write("\n", cl);
				cmd++;
			}
	if (ret != IS_OK)
		return (ret);
	return (sv_client_write(SERVER_OK_OUTPUT, cl));
}
