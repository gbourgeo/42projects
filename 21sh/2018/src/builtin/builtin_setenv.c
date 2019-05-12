/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 09:37:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/25 23:40:39 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_dprintf.h"
#include "shell_lib.h"
#include "builtin_setenv.h"
#include "main_tools.h"
#include "shell.h"

static int		setenv_error(int err, char *cmd_name, t_s_env *e)
{
	static char	*errors[] = {
		NULL, MALLOC_ERROR, MISSING_ARG, TOO_MANY_ARGS, WRONG_VAR_NAME,
		ALPHA_VAR_NAME, WRITE_ERROR,
	};

	ft_dprintf(STDERR_FILENO, "%s: ", e->progname);
	if (e->filein)
		ft_dprintf(STDERR_FILENO, "line %ld: ", e->filein);
	ft_dprintf(STDERR_FILENO, "%s: %s\n", cmd_name, errors[err]);
	return (1);
}

int				builtin_setenv(t_execute *exec, t_s_env *e)
{
	char		**ptr;

	if (!exec->cmd[1])
	{
		if (sh_puttab((const char **)e->public_env) < 0)
			return (setenv_error(ERR_WRITE, exec->cmd[0], e));
		return (0);
	}
	if (!exec->cmd[2])
		return (setenv_error(ERR_MISSING_ARG, exec->cmd[0], e));
	if (exec->cmd[3])
		return (setenv_error(ERR_TOO_MANY_ARGS, exec->cmd[0], e));
	if (!ft_isalpha(*exec->cmd[1]))
		return (setenv_error(ERR_WRONG_VAR_NAME, exec->cmd[0], e));
	if (!sh_stralnum(exec->cmd[1]))
		return (setenv_error(ERR_ALPHA_VAR_NAME, exec->cmd[0], e));
	if ((ptr = sh_getnenvaddr(exec->cmd[1], e->private_env)))
		sh_unsetenv(exec->cmd[1], e->private_env);
	if (sh_setenv(exec->cmd[1], exec->cmd[2], &e->public_env))
		return (setenv_error(ERR_MALLOC_ERROR, exec->cmd[0], e));
	if (ft_strcmp(exec->cmd[1], "PATH") == 0)
		check_path(e);
	get_tree_env();
	return (0);
}
