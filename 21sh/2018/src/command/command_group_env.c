/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_group_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 18:14:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/20 20:47:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"
#include "parser.h"
#include "command.h"

static size_t	new_env_length(t_argument *var, t_argument *cmd)
{
	size_t		length;

	length = 0;
	while (var != cmd)
	{
		length++;
		var = var->next;
	}
	return (length);
}

static size_t	new_env_fill(char **new_env, const char **env)
{
	size_t		i;

	i = 0;
	if (env)
		while (env[i])
		{
			new_env[i] = (char *)env[i];
			i++;
		}
	return (i);
}

char			**command_group_env(t_argument *var, t_argument *cmd,
const char **public, const char **private)
{
	char		**ret;
	size_t		i;

	i = new_env_length(var, cmd) + sh_tablen(public) + sh_tablen(private);
	if (!(ret = ft_memalloc(sizeof(*ret) * (i + 1))))
		return (NULL);
	i = 0;
	while (var != cmd)
	{
		ret[i] = var->cmd[0];
		++i;
		var = var->next;
	}
	i += new_env_fill(ret + i, public);
	i += new_env_fill(ret + i, private);
	return (ret);
}
