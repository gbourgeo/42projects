/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/21 00:00:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/17 16:35:37 by gbourgeo         ###   ########.fr       */
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
				ft_putstr("cd: too many levels of symbolic links: ");
			else
				ft_putstr("cd: no such file or directory: ");
		}
		else if (!S_ISDIR(buffer.st_mode))
			ft_putstr("cd: not a directory: ");
		else
			ft_putstr("cd: permission denied: ");
		ft_putendl(entry);
		free(pwd);
	}
	return (1);
}

static int		cd_write_in_pwd(char **args, int i, char ***env)
{
	char		*pwd;
	char		*tmp;

	pwd = ft_cd_check(args, env, i);
	if (pwd && !*pwd)
	{
		free(pwd);
		return (0);
	}
	if (pwd && chdir(pwd) != -1)
	{
		tmp = pwd;
		if (*args[i - 1] == '-' && ft_strlen(ft_strrchr(args[i - 1], 'P')) == 1)
		{
			pwd = ft_getcwd(tmp, data.env);
			free(tmp);
		}
		ft_change_pwds(pwd, env);
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

static int		cd_search_in_pwd(char **args, char ***env)
{
	char		*pwd;
	char		*tmp;

	pwd = ft_getenv("PWD", data.env);
	if ((tmp = ft_strstr(pwd, args[1])) == NULL)
	{
		ft_putstr_fd("cd: string not in pwd: ", 2);
		ft_putendl_fd(args[1], 2);
		return (1);
	}
	pwd = cd_change_in_pwd(pwd, tmp, args);
	if (chdir(pwd) != -1)
	{
		ft_change_pwds(pwd, env);
		ft_putendl(pwd);
		free(pwd);
		return (0);
	}
	return (cd_error(pwd, pwd));
}

int				ft_cd(char **args, char ***env)
{
	int		i;

	i = 1;
	while (args[i] && *args[i] == '-' && args[i][1] && args[i][1] != '-')
	{
		if (ft_strchr(args[i], 'P') == NULL && ft_strchr(args[i], 'L') == NULL)
		{
			ft_putstr_fd("cd: invalid option: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putendl_fd("\nusage: cd [-L|-P] [dir]", 2);
			return (1);
		}
		i++;
	}
	if (!args[i] || !args[i + 1])
		return (cd_write_in_pwd(args, i, env));
	if (!args[i + 2])
		return (cd_search_in_pwd(args + i - 1, env));
	ft_putstr_fd("cd: too much arguments: ", 2);
	ft_putendl_fd(args[1], 2);
	return (1);
}
