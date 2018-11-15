/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/21 00:00:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/04/05 15:03:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		cd_error(char *pwd, char *pwd2, char *entry)
{
	struct stat	buffer;

	if (stat(pwd, &buffer) == -1)
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
	ft_freestr(&pwd);
	ft_freestr(&pwd2);
	return (1);
}

static int		cd_write_in_pwd(char **args, t_env *e, int i)
{
	char		*old_pwd;
	char		*new_pwd;

	old_pwd = getcwd(NULL, 0);
	new_pwd = cd_get_new_pwd(args, e->env, i);
	if (chdir(new_pwd) != -1)
	{
		if (args[i - 1][0] == '-' &&
			ft_strlen(ft_strrchr(args[i - 1], 'P')) == 1)
		{
			ft_freestr(&new_pwd);
			new_pwd = getcwd(NULL, 0);
		}
		ft_change_pwds(new_pwd, old_pwd, e);
		ft_freestr(&old_pwd);
		return (0);
	}
	return (cd_error(new_pwd, old_pwd, args[i]));
}

static char		*cd_change_in_pwd(char *pwd, char *spot, char **args)
{
	char		*tmp;

	tmp = ft_strndup(pwd, ft_strlen(pwd) - ft_strlen(spot));
	pwd = ft_strjoin(tmp, args[2]);
	ft_freestr(&tmp);
	tmp = ft_strjoin(pwd, spot + ft_strlen(args[1]));
	ft_freestr(&pwd);
	return (tmp);
}

static int		cd_search_in_pwd(char **args, t_env *e)
{
	char		*old_pwd;
	char		*new_pwd;
	char		*tmp;

	old_pwd = getcwd(NULL, 0);
	if ((tmp = ft_strstr(old_pwd, args[1])) == NULL)
	{
		ft_putstr_fd("cd: string not in pwd: ", 2);
		ft_putendl_fd(args[1], 2);
		ft_freestr(&old_pwd);
		return (1);
	}
	new_pwd = cd_change_in_pwd(old_pwd, tmp, args);
	if (chdir(new_pwd) != -1)
	{
		ft_putendl(new_pwd);
		ft_change_pwds(new_pwd, old_pwd, e);
		ft_freestr(&old_pwd);
		return (0);
	}
	return (cd_error(new_pwd, old_pwd, new_pwd));
}

int				ft_cd(char **args, t_env *e)
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
		return (cd_write_in_pwd(args, e, i));
	if (!args[i + 2])
		return (cd_search_in_pwd(args + i - 1, e));
	ft_putstr_fd("cd: too much arguments: ", 2);
	ft_putendl_fd(args[1], 2);
	return (1);
}
