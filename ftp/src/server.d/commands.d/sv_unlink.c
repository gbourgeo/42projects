/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_unlink.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 04:51:26 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/24 05:18:50 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sv_main.h"

static int		unlink_err(char *cmd, char *file, t_client *cl, t_server *sv)
{
	int		ret;

	if ((ret = sv_client_write(sv->info.progname, cl)) == IS_OK)
		if ((ret = sv_client_write(": ", cl)) == IS_OK)
			if ((ret = sv_client_write(cmd, cl)) == IS_OK)
				if ((ret = sv_client_write(": can't remove '", cl)) == IS_OK)
					if ((ret = sv_client_write(file, cl)) == IS_OK)
						ret = sv_client_write("'.\n", cl);
	return (ret);
}

/*
** int err[2]:
** err[0] -> Fatal error
** err[1] -> Command error
** err[2] -> Overall error
*/

int					sv_unlink(char **cmds, t_client *cl, t_server *sv)
{
	int		i;
	char	*path;
	int		err[3];

	i = 1;
	ft_bzero(err, sizeof(err));
	if (!cmds[i] || !cmds[i][0])
		return (sv_cmd_err(ft_get_error(ERR_NB_PARAMS), cmds[0], cl, sv));
	while (cmds[i] && err[0] == IS_OK)
	{
		if (!(path = ft_strdup(cmds[i])))
			return (ERR_MALLOC);
		if ((err[0] = sv_check_path(&path, cl, &sv->info.env)) == IS_OK)
			err[1] = unlink(path);
		ft_strdel(&path);
		if (err[1])
			err[0] = unlink_err(cmds[0], cmds[i], cl, sv);
		err[2] += err[1];
		err[1] = 0;
		i++;
	}
	if (err[0] || err[2])
		return (sv_client_write(SERVER_ERR_OUTPUT, cl));
	return (sv_client_write(SERVER_OK_OUTPUT, cl));
}
