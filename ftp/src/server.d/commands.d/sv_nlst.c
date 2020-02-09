/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_nlst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 15:23:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/08 18:59:35 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

/*
** NLST
** 125, 150
** 226, 250
** 425, 426, 451
** 450
** 500, 501, 502, 421, 530
*/

int				sv_nlst(char **cmds, t_client *cl)
{
	int		errnb;

	if (FT_CHECK(g_serv.options, sv_user_mode) && !cl->login.logged)
		return (sv_response(cl, "530 Please login with USER and PASS."));
	if (cl->errnb[0] != IS_OK || cl->errnb[1] != IS_OK
	|| cl->errnb[2] != IS_OK || cl->errnb[3] != IS_OK)
		return (sv_response(cl, "421 Closing connection"));
	if (cmds[1] && (!sv_validpathname(cmds[1]) || cmds[2]))
		return (sv_response(cl, "501 %s", ft_get_error(ERR_INVALID_PARAM)));
	if (!cl->data.port && cl->data.pasv_fd < 0 && cl->data.socket < 0)
		return (sv_response(cl, "425 Use PORT or PASV first"));
	cl->data.function = sv_nlst_exec;
	if ((errnb = sv_new_pid(cmds, cl, "-p")) != IS_OK)
		errnb = sv_response(cl, "552 internal error (%s)", ft_get_error(errnb));
	return (errnb);
}

/*
** NLST [<SP> <pathname>] <CRLF>
*/

int				sv_nlst_help(t_command *cmd, t_client *cl)
{
	static char	*help[] = {
		"This command causes a list to be sent from the server to the",
		"passive DTP.  If the pathname specifies a directory or other",
		"group of files, the server should transfer a list of files",
		"in the specified directory.  If the pathname specifies a",
		"file then the server should send current information on the",
		"file.  A null argument implies the user's current working or",
		"default directory.  The data transfer is over the data",
		"connection in type ASCII or type EBCDIC.  (The user must",
		"ensure that the TYPE is appropriately ASCII or EBCDIC).",
		"Since the information on a file may vary widely from system",
		"to system, this information may be hard to use automatically",
		"in a program, but may be quite useful to a human user.", NULL
	};

	return (sv_print_help(cl, cmd, "[<pathname>]", help));
}
