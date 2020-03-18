/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_rmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 19:18:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/03/17 13:26:26 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sv_main.h"
#include "sv_struct.h"

/*
** RMD
** 250
** 500, 501, 502, 421, 530, 550
*/

int				sv_rmd(char **cmds, t_client *cl)
{
	char	*path;
	int		errnb;

	if (!sv_check_err(cl->errnb, sizeof(cl->errnb) / sizeof(cl->errnb[0])))
		return (sv_response(cl, "421 Closing connection"));
	if (FT_CHECK(g_serv.options, sv_user_mode) && !cl->login.logged)
		return (sv_response(cl, "530 not logged in"));
	if (!cmds[1] || !cmds[1][0] || !sv_validpathname(cmds[1]))
		return (sv_response(cl, "501 %s", ft_get_error(ERR_NB_PARAMS)));
	if (!(path = ft_strdup(cmds[1])))
		return (sv_response(cl, "552 internal error (memory alloc. failed)"));
	if (ft_check_path(&path, cl->pwd, cl->home) != IS_OK)
		errnb = sv_response(cl, "552 internal error (memory alloc. failed)");
	else if (access(path, F_OK) != 0)
		errnb = sv_response(cl, "550 directory not found %s",
		path + ft_strlen(cl->home) - 1);
	else if (rmdir(path) != 0)
		errnb = sv_response(cl, "550 permission denied for %s",
		path + ft_strlen(cl->home) - 1);
	else
		errnb = sv_response(cl, "250 \"%s\" directory removed",
		path + ft_strlen(cl->home) - 1);
	ft_strdel(&path);
	return (errnb);
}

/*
** RMD  <SP> <pathname> <CRLF>
*/

int				sv_rmd_help(t_command *cmd, t_client *cl)
{
	static char	*help[] = {
		"This command causes the directory specified in the pathname",
		"to be removed as a directory (if the pathname is absolute)",
		"or as a subdirectory of the current working directory (if",
		"the pathname is relative).", NULL
	};

	return (sv_print_help(cl, cmd, "<pathname>", help));
}
