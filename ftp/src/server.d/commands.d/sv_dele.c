/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_dele.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 04:51:26 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/27 01:07:23 by gbourgeo         ###   ########.fr       */
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
	int		i;
	int		errnb;

	path = NULL;
	i = 0;
	errnb = IS_OK;
	if (!cmds[1] && !sv_validpathname(cmds[i]))
		return (sv_response(cl, "501 %s", ft_get_error(ERR_INVALID_PARAM)));
	if (cl->errnb[0] != IS_OK || cl->errnb[1] != IS_OK
	|| cl->errnb[2] != IS_OK || cl->errnb[3] != IS_OK)
		return (sv_response(cl, "421 closing connection"));
	if (FT_CHECK(g_serv.options, sv_user_mode) && !cl->login.logged)
		return (sv_response(cl, "530 need to log first"));
	if (!(path = ft_strdup(cmds[i]))
	|| (errnb = sv_check_path(&path, cl)) != IS_OK)
		errnb = sv_response(cl, "552 internal error (memory alloc. failed)");
	else if (access(path, F_OK))
		errnb = sv_response(cl, "550 \"%s\" file unavailable", cmds[i]);
	else if (unlink(path))
		errnb = sv_response(cl, "450 Unable to remove file %s", cmds[i]);
	else
		errnb = sv_response(cl, "250 \"%s\" file removed", cmds[i]);
	ft_strdel(&path);
	return (errnb);
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
