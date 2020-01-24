/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_rmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 19:18:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/20 18:26:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

static int		sv_rmdir_end(int errnb, t_rmdir *e, t_client *cl, t_server *sv)
{
	if (e->path)
	{
		if (e->path[0])
			free(e->path[0]);
		free(e->path);
	}
	if (errnb)
		return (errnb);
	if (e->err[0])
		return (sv_cmd_err("failed", e->cmd, cl, sv));
	return (sv_cmd_ok("Removed directory", cl, sv));
}

/*
** (int) e.err[3] means:
**
** err[0] -> Did all the operation succeed ?
** err[1] -> Did the current operation succeed ?
** err[2] -> Did a fatal error occured ?
*/

int				sv_rmd(char **cmds, t_client *cl, t_server *sv)
{
	t_rmdir		e;
	int			i;

	i = 1;
	ft_bzero(&e, sizeof(e));
	if (!cmds[i] || !cmds[i][0])
		return (sv_cmd_err(ft_get_error(ERR_NB_PARAMS), cmds[0], cl, sv));
	e.cmd = cmds[0];
	if (!(e.path = ft_memalloc(sizeof(*e.path) * 2)))
		return (ERR_MALLOC);
	while (cmds[i] && e.err[2] == IS_OK)
	{
		if (!(e.path[0] = ft_strdup(cmds[i])))
			return (sv_rmdir_end(ERR_MALLOC, &e, cl, sv));
		e.path[1] = cmds[i];
		if ((e.err[2] = sv_check_path(e.path, cl)))
			return (sv_rmdir_end(e.err[2], &e, cl, sv));
		sv_rmdir_open(&e, cl, sv);
		ft_strdel(e.path);
		e.err[0] += e.err[1];
		e.err[1] = 0;
		i++;
	}
	return (sv_rmdir_end(e.err[2], &e, cl, sv));
}

int				sv_rmd_help(t_command *cmd, t_client *cl)
{
	int		errnb;

	if ((errnb = sv_client_write(cmd->name, cl)) == IS_OK
	&& (errnb = sv_client_write(": Remove Directory\n", cl)) == IS_OK)
		errnb = sv_client_write("\n", cl);
	return (errnb);
}
