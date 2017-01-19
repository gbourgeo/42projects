/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 03:21:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/19 03:21:43 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int				check_and_exec(char **command, char **env)
{
	static char	*builtins[] = { BUILTINS };
	static int	(*function[])(char **) = { FUNCTION };
	char		**old;
	int			i;

	i = 0;
	old = e.env;
	e.env = env;
	while (builtins[i])
	{
		if (ft_strcmp(*command, builtins[i]) == 0)
		{
			e.ret = function[i](command);
			break ;
		}
		i++;
	}
	if (!builtins[i] && *command)
		e.ret = fork_function(command, env);
	e.env = old;
	return (e.ret);
}
