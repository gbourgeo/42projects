/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 15:23:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/31 03:38:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# define _DEFAULT_SOURCE
#endif
#include <unistd.h>
#include <sys/wait.h>
#include "sv_main.h"

static int		sv_ls_fork(char **cmds, t_client *cl)
{
	pid_t		pid;
	int			ret;

	pid = fork();
	if (pid > 0)
	{
		if (wait4(pid, &ret, 0, NULL) != pid)
			return (ERR_WAIT);
		if (ret > 255)
			return (sv_client_write(SERVER_ERR_OUTPUT, cl));
		return (sv_client_write(SERVER_OK_OUTPUT, cl));
	}
	else if (pid == 0)
	{
		close(STDERR_FILENO);
		if (dup2(cl->fd, STDOUT_FILENO) < 0)
			exit(255 + ERR_DUP2);
		ret = execve(cmds[0], cmds, NULL);
		exit(255 + ERR_EXECV);
	}
	return (ERR_FORK);
}

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
	return (sv_ls_fork(cmds, cl));
}
