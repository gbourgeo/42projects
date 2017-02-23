/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 03:21:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/23 05:41:34 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int				check_and_exec(char **command, char ***env)
{
	static char	*builtins[] = { BUILTINS };
	static int	(*function[])(char **, char ***) = { FUNCTION };
	int			i;
	int			ret;

	i = 0;
	ret = 0;
	restore_term();
	while (builtins[i])
	{
		if (ft_strcmp(*command, builtins[i]) == 0)
		{
			ret = function[i](command, env);
			ft_update_env(NULL, command);
			break ;
		}
		i++;
	}
	if (!builtins[i] && *command)
		ret = fork_function(command, env, 127);
	redefine_term();
	return (ret);
}
