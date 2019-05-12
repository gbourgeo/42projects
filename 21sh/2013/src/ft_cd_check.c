/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 09:56:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/30 16:00:21 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char		*recreate_path(char *new, char **list)
{
	int			i;
	char		*tmp;

	i = 0;
	while (list[i])
	{
		tmp = ft_strrchr(new, '/') + 1;
		if (!ft_strcmp(list[i], ".."))
			*tmp = '\0';
		else if (ft_strcmp(list[i], "."))
		{
			if (new[ft_strlen(new) - 1] != '/')
				new = ft_strcat(new, "/");
			new = ft_strcat(new, list[i]);
		}
		if (chdir(new) == -1)
			return (new);
		i++;
	}
	if (new[1] && new[ft_strlen(new) - 1] == '/')
		new[ft_strlen(new) - 1] = '\0';
	return (new);
}

static char		*ft_get_path(char *path, char *pwd)
{
	char		*new;
	char		**list;

	if (!pwd || !*pwd)
		return (ft_strdup(path));
	new = ft_strnew(ft_strlen(path) + ft_strlen(pwd) + 2);
	new = ft_strcpy(new, path);
	list = ft_strsplit(pwd, '/');
	if (new && list)
		new = recreate_path(new, list);
	else
		ft_putendl_fd("cd: memory insufficiant.", 2);
	if (list)
		ft_free(&list);
	return (new);
}

char			*ft_cd_check(char **args, int i, t_env *e)
{
	char	*pwd;

	if (!args[i] || !ft_strcmp(args[i], "--") || !ft_strcmp(args[i], "~"))
	{
		pwd = ft_getenv("HOME", e->env);
		if (pwd == NULL)
			ft_putendl_fd("cd: HOME not defined", 2);
		else if (!ft_strcmp(args[i], "~"))
			return (ft_get_path(pwd, &args[1][1]));
	}
	else if (ft_strcmp(args[i], "-") == 0)
	{
		if ((pwd = ft_getenv("OLDPWD", e->env)) == NULL)
			ft_putendl_fd("cd: OLDPWD not defined", 2);
		else
			ft_putendl(pwd);
	}
	else if (*args[i] == '/')
		return (ft_get_path("/", args[i]));
	else
		return (ft_get_path(ft_getenv("PWD", e->env), args[i]));
	return (ft_strdup(pwd));
}
