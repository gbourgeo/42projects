/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/21 00:00:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2015/03/30 22:37:44 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		cd_error(char *pwd, char *entry)
{
	struct stat	buffer;
	int			ret;

	if (pwd)
	{
		ret = stat(pwd, &buffer);
		if (ret == -1)
		{
			if (lstat(pwd, &buffer) != -1)
				ft_putstr("sh1: cd: too many levels of symbolic links: ");
			else
				ft_putstr("sh1: cd: no such file or directory: ");
		}
		else if (!S_ISDIR(buffer.st_mode))
			ft_putstr("sh1: cd: not a directory: ");
		else
			ft_putstr("sh1: cd: permission denied: ");
		ft_putendl(entry);
		free(pwd);
	}
	return (1);
}

static int		cd_write_in_pwd(char **args, t_env *e, int i)
{
	char		*pwd;
	char		*tmp;

	pwd = cd_check(args, e->env, i);
	if (chdir(pwd) != -1)
	{
		tmp = pwd;
		if (args[i - 1][0] == '-' && ft_strlen(ft_strrchr(args[i - 1], 'P')) == 1)
		{
			pwd = ft_getcwd(tmp, e->env);
			free(tmp);
		}
		ft_change_pwds(pwd, e);
		free(pwd);
		return (0);
	}
	return (cd_error(pwd, args[i]));
}

static char		*cd_change_in_pwd(char *pwd, char *spot, char **args)
{
	char		*tmp1;

	pwd = ft_strndup(pwd, ft_strlen(pwd) - ft_strlen(spot));
	tmp1 = ft_strjoin(pwd, args[2]);
	free(pwd);
	pwd = ft_strjoin(tmp1, spot + ft_strlen(args[1]));
	free(tmp1);
	return (pwd);
}

static int		cd_search_in_pwd(char **args, t_env *e)
{
	char		*pwd;
	char		*tmp;

	pwd = ft_getenv("PWD", e->env);
	if ((tmp = ft_strstr(pwd, args[1])) == NULL)
	{
		ft_putstr_fd("sh1: cd: string not in pwd: ", 2);
		ft_putendl_fd(args[1], 2);
		return (1);
	}
	pwd = cd_change_in_pwd(pwd, tmp, args);
	if (chdir(pwd) != -1)
	{
		ft_change_pwds(pwd, e);
		ft_putendl(pwd);
		free(pwd);
		return (0);
	}
	return (cd_error(pwd, pwd));
}

int				ft_cd(char **args, t_env *e)
{
	int		i;

	i = 1;
	while (args[i] && *args[i] == '-' && args[i][1] && args[i][1] != '-')
	{
		if (ft_strchr(args[i], 'P') == NULL && ft_strchr(args[i], 'L') == NULL)
		{
			ft_putstr_fd("sh1: cd: invalid option: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putendl_fd("sh1: usage: cd [-L|-P] [dir]", 2);
			return (1);
		}
		i++;
	}
	if (!args[i] || !args[i + 1])
		return (cd_write_in_pwd(args, e, i));
	if (!args[i + 2])
		return (cd_search_in_pwd(args + i - 1, e));
	ft_putstr_fd("sh1: cd: too much arguments: ", 2);
	ft_putendl_fd(args[1], 2);
	return (1);
}
