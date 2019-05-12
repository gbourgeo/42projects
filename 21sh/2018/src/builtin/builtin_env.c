/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 18:53:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/26 01:28:55 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_dprintf.h"
#include "shell_lib.h"
#include "builtin_env.h"
#include "builtins.h"

int				builtin_env(t_execute *exec, t_s_env *e)
{
	t_e_opt		opt;
	int			error;

	ft_memset(&opt, 0, sizeof(opt));
	*e->ret = 0;
	if (exec->cmd[1])
	{
		opt.cmdname = exec->cmd[0];
		if (!(opt.public_env = sh_tabdup((const char **)exec->env)))
			return (env_error(ERR_MALLOC, NULL, &opt, e));
		if ((error = env_options(exec->cmd, &opt)) != ERR_OK)
			return (env_error(error, exec->cmd[opt.i], &opt, e));
		if ((error = env_exec(exec, &opt, e)) != ERR_OK)
			return (env_error(error, exec->cmd[opt.i], &opt, e));
		env_free_opt(&opt);
	}
	else if (sh_puttab((const char **)exec->env) < 0)
		return (env_error(ERR_WRITE, NULL, &opt, e));
	return (*e->ret);
}
