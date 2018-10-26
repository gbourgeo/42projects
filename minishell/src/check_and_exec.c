/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 20:58:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/26 08:55:11 by gbourgeo         ###   ########.fr       */
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
		e->ret = fork_function(command, env, e->progname);
	e->env = old;
	return (e->ret);
}
