/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_nlst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 15:23:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/25 16:36:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
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
** NLST [<SP> <pathname>] <CRLF>
*/

int				sv_nlst_help(t_command *cmd, t_client *cl)
{
	static char	*help[] = {
		"This command causes a directory listing to be sent.",
		"The pathname should specify a directory or other",
		"system-specific file group descriptor; a null argument",
		"implies the current directory.  The server will return",
		"a stream of names of files and no other information.",
		"The data will be transferred in ASCII or EBCDIC type",
		"over the data connection as valid pathname strings",
		"separated by <CRLF> or <NL>.  (Again the user must",
		"ensure that the TYPE is correct.)", NULL
	};

	return (sv_print_help(cl, cmd, "[<pathname>]", help));
}
