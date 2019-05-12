/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_source.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 20:58:41 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/23 11:41:12 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "libft.h"
#include "builtin_source.h"
#include "ft_dprintf.h"
#include "shell.h"
#include "builtins.h"

static int	builtin_source_access(char *path)
{
	struct stat	buf;

	if (!path)
		return (ERR_MALLOC);
	if (access(path, F_OK))
		return (ERR_NO_SUCH_FILE);
	if (access(path, R_OK))
		return (ERR_PERMISSION);
	if (stat(path, &buf))
		return (ERR_NO_SUCH_FILE);
	if (S_ISDIR(buf.st_mode))
		return (ERR_IS_DIR);
	return (ERR_OK);
}

static int	source_usage(char *cmd)
{
	ft_dprintf(STDERR_FILENO, "%s: usage: %s filename [arguments]\n",
	cmd, cmd);
	return (2);
}

static int	source_error(int err, char **cmd, t_s_env *e)
{
	static char *errors[] = {
		NULL, "is a directory", "filename argument required",
		"no such file or directory", "permission denied", "malloc failed",
		"file not found",
	};

	ft_dprintf(STDERR_FILENO, "%s: ", e->progname);
	if (e->filein)
		ft_dprintf(STDERR_FILENO, "line %ld: ", e->filein);
	if (err != ERR_NOT_ARG)
		ft_dprintf(STDERR_FILENO, "%s: ", cmd[1]);
	ft_dprintf(STDERR_FILENO, "%s\n", errors[err]);
	if (err == ERR_NOT_ARG)
		return (source_usage(cmd[0]));
	return (1);
}

int			builtin_source(t_execute *exec, t_s_env *e)
{
	int		fd;
	int		err;
	char	*tmp_progname;

	tmp_progname = e->progname;
	if (!exec->cmd[1])
		return (source_error(ERR_NOT_ARG, exec->cmd, e));
	if ((err = builtin_source_access(exec->cmd[1])) != ERR_OK)
		return (source_error(err, exec->cmd, e));
	if ((fd = open(exec->cmd[1], O_RDONLY)) < 0)
		return (source_error(ERR_PERMISSION, exec->cmd, e));
	e->progname = exec->cmd[1];
	launch_rc(e, fd);
	close(fd);
	e->progname = tmp_progname;
	return (*e->ret);
}
