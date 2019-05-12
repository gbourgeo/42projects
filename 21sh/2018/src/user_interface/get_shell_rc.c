/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shell_rc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 14:16:30 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/23 11:25:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"
#include "shell_env.h"
#include "shell_lib.h"
#include "builtins.h"

void		launch_rc(t_s_env *e, int fd)
{
	char	*line;
	size_t	save;

	save = e->filein;
	e->filein = 1;
	line = sh_get_file(fd);
	if (line)
	{
		launch_new_cmd(&line, e);
		ft_strdel(&line);
	}
	e->filein = save;
}

static int	get_shell_rc(t_execute *exec)
{
	if (!(exec->cmd[1] = getenv("HOME")))
	{
		free(exec->cmd);
		return (1);
	}
	exec->cmd[1] = ft_strjoin(exec->cmd[1], "/");
	exec->cmd[1] = ft_strjoinfree(exec->cmd[1], RC_NAME, 1);
	if (access(exec->cmd[1], F_OK))
	{
		free(exec->cmd[1]);
		free(exec->cmd);
		return (1);
	}
	return (0);
}

void		get_rc(t_s_env *e, char *relative)
{
	t_execute	exec;

	exec.cmd = ft_memalloc(sizeof(char**) * 2);
	exec.cmd[0] = e->av[1];
	if (!relative)
	{
		if (get_shell_rc(&exec))
			return ;
	}
	else
		exec.cmd[1] = ft_strdup(relative);
	builtin_source((t_execute*)&exec, e);
	e->filein = e->ac != 1;
	free(exec.cmd[1]);
	free(exec.cmd);
}
