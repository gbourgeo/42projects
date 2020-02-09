/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_cdup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 17:53:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/08 18:26:25 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"
#include "sv_struct.h"

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
		"syntaxes for naming the parent directory.", NULL
	};

	return (sv_print_help(cl, cmd, "", help));
}
