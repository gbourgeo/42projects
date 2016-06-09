/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_lcd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/27 03:04:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/08/26 22:15:14 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

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
				ft_putstr("\033[31mERROR: lcd: too many level of symbolinks: ");
			else
				ft_putstr("\033[31mERROR: lcd: no such file or directory: ");
		}
		else if (!S_ISDIR(buffer.st_mode))
			ft_putstr_fd("\033[31mERROR: lcd: not a directory: ", 2);
		else
			ft_putstr_fd("\033[31mERROR: lcd: permission denied: ", 2);
		ft_putendl_fd(entry, 2);
		free(pwd);
	}
	return (1);
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

static int		cd_search_in_pwd(char **args, t_envi *cl)
{
	char		*pwd;
	char		*tmp;

	pwd = cl->lpwd;
	if ((tmp = ft_strstr(pwd, args[1])) == NULL)
	{
		ft_putstr_fd("\033[31mERROR: lcd: string not in pwd: ", 2);
		ft_putendl_fd(args[1], 2);
		return (1);
	}
	pwd = cd_change_in_pwd(pwd, tmp, args);
	if (chdir(pwd) != -1)
	{
		cl_change_pwds(pwd, cl);
		ft_putendl(cl->pwd);
		free(pwd);
		return (0);
	}
	return (cd_error(pwd, pwd));
}

static int		cd_write_in_pwd(char **args, t_envi *cl)
{
	char		*pwd;
	char		*tmp;

	pwd = ft_get_path(args[1], cl->home, cl->lpwd, cl->oldpwd);
	if (chdir(pwd) != -1)
	{
		tmp = pwd;
		if (args[0][0] == '-' && ft_strlen(ft_strrchr(args[0], 'P')) == 1)
		{
			pwd = getcwd(NULL, 0);
			free(tmp);
		}
		cl_change_pwds(pwd, cl);
		if (!ft_strcmp(args[1], "-"))
			ft_putendl(pwd);
		free(pwd);
		return (0);
	}
	return (cd_error(pwd, args[1]));
}

int				cl_lcd(char **args, t_envi *cl)
{
	int			i;

	i = 1;
	while (args[i] && args[i][0] == '-' && args[i][1] && args[i][1] != '-')
	{
		if (ft_strchr(args[i], 'P') == NULL && ft_strchr(args[i], 'L') == NULL)
		{
			ft_putendl_fd("\033[31mERROR: lcd: invalid option(s)", 2);
			ft_putendl_fd("\033[31mERROR: usage: lcd [-L|-P] [dir]", 2);
			return (1);
		}
		i++;
	}
	if (!args[i] || !args[i + 1])
		return (cd_write_in_pwd(args + i - 1, cl));
	if (!args[i + 2])
		return (cd_search_in_pwd(args + i - 1, cl));
	ft_putendl_fd("\033[31mERROR: lcd: too much arguments", 2);
	return (1);
}
