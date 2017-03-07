/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 03:21:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/07 19:20:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			check_and_exec(char **command, t_env *e)
{
	static char	*builtins[] = { BUILTINS };
	static void	(*function[])(char **, t_env *) = { FUNCTION };
	char		*path;
	int			i;

	i = 0;
	restore_term();
	while (builtins[i])
	{
		if (ft_strcmp(*command, builtins[i]) == 0)
		{
			ft_update_env(NULL, command, e);
			function[i](command, e);
			break ;
		}
		i++;
	}
	if (!builtins[i] && *command)
	{
		path = fork_function(command, e);
		ft_update_env(path, command, e);
	}
	redefine_term();
}
