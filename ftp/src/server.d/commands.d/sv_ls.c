/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 15:23:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/22 17:10:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sv_main.h"

int				sv_ls(char **cmds, t_client *cl, t_server *sv)
{
	char		*cmdpath;
	int			i;
	int			errnb;

	if (!(cmdpath = ft_get_command(cmds[0], sv->info.env.path, 0)))
		return (IS_OK);
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
