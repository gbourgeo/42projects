/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_opt_u.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 14:34:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/29 13:53:59 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_dprintf.h"
#include "shell_lib.h"
#include "builtin_env.h"

int			env_opt_u(char **cmd, t_e_opt *opt)
{
	char	*var;

	if (!cmd[opt->i][opt->j + 1] && !cmd[opt->i + 1])
		return (ERR_NEED_ARG);
	opt->options |= BUILTIN_OPT_U;
	var = (cmd[opt->i][opt->j + 1])
		? &cmd[opt->i][opt->j + 1] : cmd[++(opt->i)];
	if (opt->options & BUILTIN_OPT_V)
	{
		if (ft_dprintf(STDERR_FILENO, "#%s unset:\t%s\n",
		opt->cmdname, var) < 0)
			return (ERR_WRITE);
	}
	sh_unsetenv(var, opt->public_env);
	return (ERR_OK);
}
