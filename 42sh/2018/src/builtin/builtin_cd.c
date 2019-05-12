/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 08:20:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/23 09:04:14 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_env.h"
#include "builtin_cd.h"
#include "builtins.h"

static int		cd_args_loop(char *arg, t_cd *cd, t_s_env *e)
{
	size_t		i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] == 'P')
		{
			cd->options &= ~(CD_OPT_L);
			cd->options |= CD_OPT_P;
		}
		else if (arg[i] == 'L')
		{
			cd->options &= ~(CD_OPT_P);
			cd->options |= CD_OPT_L;
		}
		else
			return (cd_error(ERR_INVALID_OPTION, &arg[i], e));
		i++;
	}
	return (0);
}

static size_t	cd_args(char **args, t_cd *cd, t_s_env *e)
{
	size_t		i;

	i = 1;
	while (args[i] && args[i][0] == '-')
	{
		if (!args[i][1])
		{
			cd->options |= CD_OPT_BACK;
			break ;
		}
		if (!ft_strcmp(args[i], "--"))
			return (i + 1);
		if (cd_args_loop(args[i], cd, e))
			return (0);
		i++;
	}
	return (i);
}

int				builtin_cd(t_execute *exec, t_s_env *e)
{
	t_cd		cd;
	size_t		i;

	ft_memset(&cd, 0, sizeof(cd));
	if (!(i = cd_args(exec->cmd, &cd, e)))
		return (1);
	if (!exec->cmd[i] || !exec->cmd[i + 1])
		return (cd_write_in_pwd(exec, e, i));
	if (!exec->cmd[i + 2])
		return (cd_search_in_pwd(exec, e, i - 1));
	return (cd_error(ERR_TOO_MUCH_ARGUMENT, exec->cmd[1], e));
}
