/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_cdup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 17:53:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/18 20:14:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

typedef struct	s_cdup
{
	char	*cmd;
	char	*arg;
	char	*null;
}				t_cdup;

int					sv_cdup(char **cmds, t_client *cl, t_server *sv)
{
	return (sv_cwd((char **)&(t_cdup){ cmds[0], "..", NULL }, cl, sv));
}

int					sv_cdup_help(t_command *cmd, t_client *cl)
{
	int		errnb;

	if ((errnb = sv_client_write(cmd->name, cl)) == IS_OK
	&& (errnb = sv_client_write(": Change Directory UP\n", cl)) == IS_OK)
		errnb = sv_client_write("\n", cl);
	return (errnb);
}
