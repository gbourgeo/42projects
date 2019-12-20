/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_help.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:31:05 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/20 17:40:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int					sv_help(char **cmds, t_client *cl, t_server *sv)
{
	t_command		*cmd;
	int				ret;
	int				size;
	char			*spacing;

	cmd = (t_command *)cmds;
	ret = IS_OK;
	size = sv_getcommandsright(cl->user.rights);
	if ((ret = sv_client_write(sv->info.progname, cl)) == IS_OK)
		if ((ret = sv_client_write(": -- HELP\n\n", cl)) == IS_OK)
			while (size-- && ret == IS_OK)
			{
				spacing = (ft_strlen(cmd[size].name) > 6) ? "\t" : "\t\t";
				if ((ret = sv_client_write(cmd[size].name, cl)) == IS_OK)
					if ((ret = sv_client_write(spacing, cl)) == IS_OK)
						if ((ret = sv_client_write(cmd[size].descrip, cl))
							== IS_OK)
							ret = sv_client_write("\n", cl);
			}
	if (ret != IS_OK)
		return (ret);
	return (sv_client_write(OK_OUTPUT, cl));
}
