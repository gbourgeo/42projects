/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/20 23:26:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/16 20:36:28 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_dprintf.h"
#include "shell_lib.h"
#include "builtins.h"

int				builtin_unsetenv(t_execute *exec, t_s_env *e)
{
	size_t		i;

	i = 1;
	if (!exec->cmd[i])
	{
		ft_dprintf(STDERR_FILENO, "%s: ", e->progname);
		if (e->interactive)
			ft_dprintf(STDERR_FILENO, "line %ld: ", e->interactive);
		ft_dprintf(STDERR_FILENO, "%s: missing argument\n", exec->cmd[0]);
		return (1);
	}
	while (exec->cmd[i])
	{
		sh_unsetenv(exec->cmd[i], e->public_env);
		sh_unsetenv(exec->cmd[i], e->private_env);
		i++;
	}
	return (0);
}
