/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_cdup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 17:53:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/23 00:11:16 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

typedef struct	s_cdup
{
	char	*cmd;
	char	*arg;
	char	*null;
}				t_cdup;

int				sv_cdup(char **cmds, t_client *cl)
{
	return (sv_cwd((char **)&(t_cdup){ cmds[0], "..", NULL }, cl));
}

int				sv_cdup_help(t_command *cmd, t_client *cl)
{
	static char	*help[] = {
		"This command is a special case of CWD, and is included to",
		"simplify the implementation of programs for transferring",
		"directory trees between operating systems having different",
		"syntaxes for naming the parent directory.",
	};
	long	i;
	int		errnb;

	i = 0;
	errnb = sv_response(cl, "214-%s", cmd->name, cmd->descrip);
	while (errnb == IS_OK && help[i + 1])
	{
		errnb = sv_response(cl, "%s", help[i]);
		i++;
	}
	if (errnb == IS_OK)
		errnb = sv_response(cl, "214 %s", help[i]);
	return (errnb);
}
