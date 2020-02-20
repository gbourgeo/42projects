/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_dele.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/31 04:51:26 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/19 18:47:17 by gbourgeo         ###   ########.fr       */
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
	int		errnb;

	path = NULL;
	errnb = IS_OK;
	if (FT_CHECK(g_serv.options, sv_user_mode) && !cl->login.logged)
		return (sv_response(cl, "530 Please login with USER and PASS."));
	if (!sv_check_err(cl->errnb, sizeof(cl->errnb) / sizeof(cl->errnb[0])))
		return (sv_response(cl, "421 Closing connection"));
	if (!cmds[1] && !sv_validpathname(cmds[1]))
		return (sv_response(cl, "501 %s", ft_get_error(ERR_INVALID_PARAM)));
	if (!(path = ft_strdup(cmds[1]))
	|| (errnb = ft_check_path(&path, cl->pwd, cl->home)) != IS_OK)
		errnb = sv_response(cl, "552 Internal error (memory alloc. failed)");
	else if (access(path, F_OK))
		errnb = sv_response(cl, "550 \"%s\" file unavailable", cmds[1]);
	else if (unlink(path))
		errnb = sv_response(cl, "450 Unable to remove file %s", cmds[1]);
	else
		errnb = sv_response(cl, "250 \"%s\" file removed", cmds[1]);
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
