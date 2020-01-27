/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_nlst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 15:23:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/27 20:19:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sv_main.h"

// static int 		done(char *arg, t_client *cl)
// {
// 	char		**cmds;
// 	int			i;
// 	int			errnb;

// 	i = 0;
// 	if (!(cmds = malloc(sizeof(*cmds) * 3)) || !(cmds[0] = ft_strdup("/bin/ls"))
// 	|| sv_check_path(&arg, cl) != IS_OK)
// 		return (ERR_MALLOC);
// 	else if (access(arg, F_OK) != 0)
// 		errnb = ERR_INVALID_PARAM;
// 	else if (dup2(cl->data.socket, STDOUT_FILENO) < 0)
// 		errnb = ERR_DUP2;
// 	else
// 	{
// 		close(STDERR_FILENO);
// 		cmds[1] = arg;
// 		execve(cmds[0], cmds, NULL);
// 	}
// 	ft_tabdel(&cmds);
// 	return (ERR_EXECV);
// }

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
	char	*path;
	int		errnb;

	if (cmds[1] && (!sv_validpathname(cmds[1]) || cmds[2]))
		return (sv_response(cl, "501 %s", ft_get_error(ERR_INVALID_PARAM)));
	if (cl->errnb[0] != IS_OK || cl->errnb[1] != IS_OK
	|| cl->errnb[2] != IS_OK || cl->errnb[3] != IS_OK)
		return (sv_response(cl, "421 closing connection"));
	if (FT_CHECK(g_serv.options, sv_user_mode) && !cl->login.logged)
		return (sv_response(cl, "530 not logged in"));
	if (cl->data.fd <= 0 && cl->data.socket <= 0)
		return (sv_response(cl, "425 no data connection established"));
	// else if ((errnb = sv_new_pid(cmds, cl, done)) != IS_OK)
	// 	errnb = sv_response(cl, "552 internal error (%s)", ft_get_error(errnb));
	errnb = IS_OK;
	ft_strdel(&path);
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
