/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_system.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 08:13:28 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/15 19:48:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "shell_lib.h"
#include "command.h"
#include "command_error.h"

static void		command_execve(char *name, t_execute *exec, t_s_env *e)
{
	pid_t		pid;
	size_t		len;

	pid = 0;
	if (e->forked || (pid = fork()) == 0)
	{
		len = sh_tablen((const char **)exec->env);
		len -= sh_tablen((const char **)e->private_env);
		exec->env[len] = NULL;
		execve(name, exec->cmd, exec->env);
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
		command_wait(pid, 0, e->ret);
	else if (pid < 0)
		*e->ret = command_error(e->progname, ERR_FORK, exec->cmd, e);
}

int				command_system(t_execute *exec, t_s_env *e)
{
	char		*name;
	int			error;

	name = NULL;
	if ((error = command_redirect(exec->fds, exec->redirection)))
		command_error(e->progname, error, NULL, e);
	else if ((error = command_path(&name, exec->cmd[0],
	sh_getnenv("PATH", exec->env))))
		command_error(e->progname, error, exec->cmd, e);
	else if ((error = command_access(name, exec->cmd[0])))
		command_error(e->progname, error, exec->cmd, e);
	else
		command_execve(name, exec, e);
	if (name)
		free(name);
	if ((error = command_restore_fds(exec->fds)))
		command_error(e->progname, error, NULL, e);
	return (ERR_OK);
}
