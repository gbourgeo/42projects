/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_write.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 11:01:36 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/29 13:48:01 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/param.h>
#include "libft.h"
#include "shell_lib.h"
#include "builtin_cd.h"

int				cd_get_path(char *pwd, char *cmd)
{
	if (*cmd == '/')
		ft_strncpy(pwd, cmd, MAXPATHLEN);
	else if (getcwd(pwd, MAXPATHLEN) == NULL)
		return (ERR_GETCWD);
	else
	{
		ft_strncat(pwd, "/", MAXPATHLEN);
		ft_strncat(pwd, cmd, MAXPATHLEN);
	}
	pwd = cd_recreate_path(pwd);
	return (ERR_NO_ERR);
}

static int		cd_get_new_pwd(char *cmd, char *pwd, char **env)
{
	char		*path;

	if (!cmd)
	{
		if (!(path = sh_getnenv("HOME", env)))
			return (ERR_NO_HOME);
	}
	else if (!ft_strcmp(cmd, "-"))
	{
		if (!(path = sh_getnenv("OLDPWD", env)))
			return (ERR_NO_OLDPWD);
	}
	else
		return (cd_get_path(pwd, cmd));
	ft_strncpy(pwd, path, MAXPATHLEN);
	return (ERR_NO_ERR);
}

int				cd_write_in_pwd(t_execute *exec, t_s_env *e, size_t i)
{
	char		new_pwd[MAXPATHLEN];
	int			ret;

	if ((ret = cd_get_new_pwd(exec->cmd[i], new_pwd, exec->env)) != ERR_NO_ERR)
		return (cd_error(ret, exec->cmd[i], e));
	if (*new_pwd && chdir(new_pwd) < 0)
		return (cd_dir_error(new_pwd, exec->cmd[i], e));
	if (exec->cmd[i - 1][0] == '-'
	&& exec->cmd[i - 1][ft_strlen(exec->cmd[i - 1]) - 1] == 'P')
	{
		if (getcwd(new_pwd, MAXPATHLEN) == NULL)
			return (ERR_GETCWD);
	}
	if ((ret = cd_change_pwds(new_pwd, exec->env, e)) == ERR_NO_ERR)
		if (exec->cmd[i] && !ft_strcmp(exec->cmd[i], "-"))
			if (sh_putendl_fd(new_pwd, STDOUT_FILENO) < 0)
				return (cd_error(ERR_WRITE, NULL, e));
	return ((ret) ? cd_error(ret, exec->cmd[i], e) : ERR_NO_ERR);
}
