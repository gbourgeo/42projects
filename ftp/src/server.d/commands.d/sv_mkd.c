/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_mkd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:40:33 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/03/17 13:21:24 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "sv_main.h"
#include "sv_struct.h"

/*
** MKD
** 257
** 500, 501, 502, 421, 530, 550
*/

int				sv_mkd(char **cmds, t_client *cl)
{
	char		*dir;
	int			errnb;

	if (FT_CHECK(g_serv.options, sv_user_mode) && !cl->login.logged)
		return (sv_response(cl, "530 Please login with USER and PASS."));
	if (!sv_check_err(cl->errnb, sizeof(cl->errnb) / sizeof(cl->errnb[0])))
		return (sv_response(cl, "421 Closing connection"));
	if (!cmds[1] || !cmds[1][0] || !sv_validpathname(cmds[1]))
		return (sv_response(cl, "501 %s", ft_get_error(ERR_INVALID_PARAM)));
	if (!(dir = ft_strdup(cmds[1]))
	|| ft_check_path(&dir, cl->pwd, cl->home) != IS_OK)
		errnb = sv_response(cl, "552 internal error (memory alloc. failed)");
	else if (mkdir(dir, 0777) != 0)
		errnb = sv_response(cl, "550 Failed to create %s",
		dir + ft_strlen(cl->home) - 1);
	else
		errnb = sv_response(cl, "257 \"%s\" directory created",
		dir + ft_strlen(cl->home) - 1);
	ft_strdel(&dir);
	return (errnb);
}

/*
** MKD <SP> <chemin d'accès> <CRLF>
*/

int				sv_mkd_help(t_command *cmd, t_client *cl)
{
	static char	*help[] = {
		"This command causes the directory specified in the pathname",
		"to be created as a directory (if the pathname is absolute)",
		"or as a subdirectory of the current working directory (if",
		"the pathname is relative).", NULL
	};

	return (sv_print_help(cl, cmd, "<pathname>", help));
}
