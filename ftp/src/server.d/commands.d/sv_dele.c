/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_dele.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 04:51:26 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/25 20:53:06 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sv_main.h"

/*
** DELE
** 250
** 450, 550
** 500, 501, 502, 421, 530
*/

int				sv_dele(char **cmds, t_client *cl)
{
	char	*path;
	int		err[2];
	int		i;

	ft_bzero(err, sizeof(err));
	i = 0;
	if (!cmds[1])
		return (sv_response(cl, "501 Syntax error"));
	while (cmds[++i] && err[0] == IS_OK)
	{
		if (!sv_validpathname(cmds[i]))
			err[0] = sv_response(cl, "553 \"%s\" filename not allowed", cmds[i]);
		if (!(path = ft_strdup(cmds[i])))
			err[0] = sv_response(cl, "552 \"%s\" allocation failed", cmds[i]);
		else if ((err[0] = sv_check_path(&path, cl)) != IS_OK)
			err[0] = sv_response(cl, "552 \"%s\" allocation failed", cmds[i]);
		else if (access(path, F_OK))
			err[0] = sv_response(cl, "550 \"%s\" file unavailable", cmds[i]);
		else if (unlink(path))
			err[0] = sv_response(cl, "450 Unable to remove file %s", cmds[i]);
		else
			err[0] = sv_response(cl, "250 \"%s\" file removed", cmds[i]);
		ft_strdel(&path);
	}
	return (err[0]);
}

/*
** DELE <SP> <chemin d'accès> <CRLF>
*/

int				sv_dele_help(t_command *cmd, t_client *cl)
{
	static char	*help[] = {
		"This command causes the file specified in the pathname to be",
		"deleted at the server site.", NULL
	};

	return (sv_print_help(cl, cmd, "<pathname>", help));
}
