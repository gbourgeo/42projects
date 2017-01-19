/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/20 23:26:39 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/27 19:17:51 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int		search_in_env(char **args, char **env)
{
	int		i;

	i = 0;
	if (env)
	{
		while (env[i] != 0)
		{
			if (ft_strcmp(env[i], args[1]) == '=')
				return (i);
			i++;
		}
	}
	return (-1);
}

static void		modify_env(char **args, char **env, int i)
{
	char		*modif;

	modif = ft_strjoin(args[1], "=");
	free(env[i]);
	env[i] = ft_strjoin(modif, args[2]);
	free(modif);
	modif = NULL;
}

static char		**new_env(char **args, char ***env)
{
	char	**new;
	char	*join;
	int		i;

	i = ft_tablen(*env);
	if ((new = (char**)malloc(sizeof(char*) * (i + 2))) == NULL)
		return (NULL);
	i = 0;
	if ((*env))
	{
		while ((*env)[i])
		{
			new[i] = ft_strdup((*env)[i]);
			i++;
		}
		ft_free(env);
	}
	join = ft_strjoin(args[1], "=");
	new[i] = ft_strjoin(join, args[2]);
	new[i + 1] = '\0';
	free(join);
	return (new);
}

int				ft_setenv(char **args, char ***env)
{
	int		ret;

	ret = 0;
	if (args[1] == '\0' || ft_strchr(args[1], '='))
		ft_putendl("setenv: bad assignment");
	else
	{
		if ((ret = search_in_env(args, *env)) >= 0)
			modify_env(args, *env, ret);
		else
			*env = new_env(args, env);
		if (*env)
			return (0);
	}
	return (-1);
}
