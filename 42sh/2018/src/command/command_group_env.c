/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_group_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 18:14:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/29 15:22:33 by gbourgeo         ###   ########.fr       */
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

static size_t	new_env_fill(char **new_env, size_t len, const char **env)
{
	size_t		i;
	size_t		j;
	size_t		match;

	i = 0;
	match = 0;
	if (env)
		while (env[i])
		{
			j = 0;
			while (j < len && new_env[j]
			&& ft_strcmp(new_env[j], env[i]) != '=')
				j++;
			if (len == 0 || j == len)
				new_env[len + i - match] = ft_strdup((char *)env[i]);
			else
				match++;
			i++;
		}
	return (i);
}

char			**command_group_env(t_argument *var, t_argument *cmd,
const char **public)
{
	char		**ret;
	size_t		i;

	i = new_env_length(var, cmd) + sh_tablen(public);
	if (!(ret = ft_memalloc(sizeof(*ret) * (i + 1))))
		return (NULL);
	i = 0;
	while (var != cmd)
	{
		ret[i] = ft_strdup(var->cmd[0]);
		++i;
		var = var->next;
	}
	i += new_env_fill(ret, i, public);
	return (ret);
}
