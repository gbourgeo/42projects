/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 09:56:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/27 19:15:15 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static char		*check_if_good_env(char **args, char ***env)
{
	if (!args[1] || !ft_strcmp(args[1], "--") || !ft_strcmp(args[1], "~"))
	{
		if (ft_getenv("HOME", *env) && (!args[1] || !ft_strcmp(args[1], "--")))
			return (ft_strdup(ft_getenv("HOME", *env)));
		else if (ft_getenv("HOME", *env) && !ft_strcmp(args[1], "~"))
			return (ft_strjoin(ft_getenv("HOME", *env), &args[1][1]));
		ft_putendl_fd("42sh: cd: HOME not defined", 2);
		return (ft_strdup(ft_getenv("PWD", *env)));
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		if (ft_getenv("OLDPWD", *env))
		{
			ft_putendl(ft_getenv("OLDPWD", *env));
			return (ft_strdup(ft_getenv("OLDPWD", *env)));
		}
		ft_putendl_fd("42sh: cd: OLDPWD not defined", 2);
		return (ft_strdup(ft_getenv("PWD", *env)));
	}
	return (NULL);
}

char			*cd_check(char **args, char ***env)
{
	char	*pwd;
	char	*dir;

	if ((pwd = check_if_good_env(args, env)))
		return (ft_get_path(pwd));
	else if (args[1][0] == '/')
		pwd = ft_strdup(args[1]);
	else
	{
		dir = ft_strjoin(ft_getenv("PWD", *env), "/");
		pwd = ft_strjoin(dir, args[1]);
		free(dir);
	}
	return (ft_get_path(pwd));
}
