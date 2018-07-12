/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 10:30:02 by root              #+#    #+#             */
/*   Updated: 2018/07/12 10:30:09 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int				check_and_exec(char **command, char **env, t_env *e)
{
	static char	*builtins[] = { BUILTINS };
	static int	(*function[])(char **, t_env *) = { FUNCTION };
	char		**old;
	int			i;

	i = 0;
	old = e->env;
	e->env = env;
	while (builtins[i])
	{
		if (ft_strcmp(*command, builtins[i]) == 0)
		{
			e->ret = function[i](command, e);
			return (e->ret);
		}
		i++;
	}
	if (*command)
		e->ret = fork_function(command, env);
	e->env = old;
	return (e->ret);
}
