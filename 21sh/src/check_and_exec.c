/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 03:21:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/21 20:45:33 by gbourgeo         ###   ########.fr       */
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
	while (builtins[i])
	{
		if (ft_strcmp(*command, builtins[i]) == 0)
		{
			ret = function[i](command, env);
			ft_update_env(NULL, command);
			return (ret);
		}
		i++;
	}
	if (!builtins[i] && *command)
		ret = fork_function(command, env, 127);
	return (ret);
}
