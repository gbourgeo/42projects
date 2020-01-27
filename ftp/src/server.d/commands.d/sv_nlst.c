/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_nlst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 15:23:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/27 03:21:22 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sv_main.h"

int done(char **cmds,t_client *cl)
{
	char		*cmdpath;
	int			i;
	int			errnb;

	// if (!(cmdpath = ft_get_command("ls", sv->info.env.path, 0)))
	// 	return (IS_OK);
	cmdpath = ft_strdup("/bin/ls");
	free(cmds[0]);
	cmds[0] = cmdpath;
	i = 0;
	while (cmds[++i])
		if ((errnb = sv_check_path(&cmds[i], cl)) != IS_OK)
			return (errnb);
	cl->pid_ls = fork();
	if (cl->pid_ls < 0)
		return (ERR_FORK);
	else if (cl->pid_ls == 0)
	{
		close(STDERR_FILENO);
		if (dup2(cl->fd, STDOUT_FILENO) < 0)
			exit(ERR_DUP2);
		execve(cmds[0], cmds, NULL);
		exit(ERR_EXECV);
	}
	return (IS_OK);
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
	char	*path;
	int		errnb;

	if (cmds[1] && !sv_validpathname(cmds[1]))
		return (sv_response(cl, "501 %s", ft_get_error(ERR_INVALID_PARAM)));
	if (cl->errnb[0] != IS_OK || cl->errnb[1] != IS_OK
	|| cl->errnb[2] != IS_OK || cl->errnb[3] != IS_OK)
		return (sv_response(cl, "421 closing connection"));
	if (FT_CHECK(g_serv.options, sv_user_mode) && !cl->login.logged)
		return (sv_response(cl, "530 not logged in"));
	if (!(path = (cmds[1]) ? ft_strdup(cmds[1]) : ft_strdup(".")))
		return (sv_response(cl, "552 internal error (memory alloc. failed)"));
	if (sv_check_path(&path, cl) != IS_OK)
		errnb = sv_response(cl, "552 internal error (memory alloc. failed)");
	else if (access(path, F_OK) != 0)
		errnb = sv_response(cl, "550 directory/file not found %s",
		path + ft_strlen(cl->home) - 1);
	else
		;
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
