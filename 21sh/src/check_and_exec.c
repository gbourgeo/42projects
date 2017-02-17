/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 03:21:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/17 19:46:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int				check_and_exec(char **command, char ***env)
{
	static char	*builtins[] = { BUILTINS };
	static int	(*function[])(char **, char ***) = { FUNCTION };
	int			i;

	i = 0;
	data.ret = 0;
	while (builtins[i])
	{
		if (ft_strcmp(*command, builtins[i]) == 0)
		{
			data.ret = function[i](command, env);
			break ;
		}
		i++;
	}
	if (!builtins[i] && *command)
		data.ret = fork_function(command, env, 127);
	return (data.ret);
}
