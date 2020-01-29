/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_nlst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 15:23:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/29 19:16:07 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sv_main.h"

static int		fill_command(char **cmd, char **arg, t_client *cl)
{
	struct stat		buf;

	if (arg[1])
	{
		if (sv_check_path(&arg[1], cl) != IS_OK)
			return (ERR_MALLOC);
		if (stat(arg[1], &buf) != 0)
			return (ERR_WRONG_PARAM);
		cmd[2] = arg[1] + ft_strlen(cl->home);
	}
	return (IS_OK);
}

static int 		sv_nlst_exec(char **arg, t_client *cl)
{
	char		**cmd;
	int			errnb;

	errnb = IS_OK;
	if (!(cmd = ft_memalloc(sizeof(*cmd) * 4)))
		return (ERR_MALLOC);
	if (!(cmd[0] = ft_strdup("/bin/ls")) || !(cmd[1] = ft_strdup("-p")))
		errnb = ERR_MALLOC;
	else if ((errnb = fill_command(cmd, arg, cl)) == IS_OK)
	{
		ft_puttab(cmd);
		if (dup2(cl->data.socket, STDOUT_FILENO) < 0)
			errnb = ERR_DUP2;
		else
		{
			close(STDERR_FILENO);
			execve(cmd[0], cmd, NULL);
			errnb = ERR_EXECV;
		}
	}
	ft_strdel(&cmd[0]);
	ft_strdel(&cmd[1]);
	ft_strdel(cmd);
	return (errnb);
}

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
	if ((errnb = sv_new_pid(cmds, cl, sv_nlst_exec)) != IS_OK)
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
