/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_search.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 06:03:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/21 19:32:18 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/param.h>
#include "libft.h"
#include "shell_lib.h"
#include "shell_env.h"
#include "builtin_cd.h"

static char		*cd_change_string(char *pwd, char *ptr, char *s1, char *s2)
{
	char		save[MAXPATHLEN];
	char		*end;

	end = ptr + ft_strlen(s1);
	ft_strcpy(save, end);
	ft_memset(ptr, 0, ft_strlen(s1));
	if (ft_strlen(pwd) + ft_strlen(s2) + ft_strlen(end) >= MAXPATHLEN)
		return (NULL);
	ft_strcpy(ptr, s2);
	ft_strcat(pwd, save);
	cd_recreate_path(pwd);
	return (pwd);
}

int				cd_search_in_pwd(t_execute *exec, t_s_env *e, size_t i)
{
	char		new_pwd[MAXPATHLEN];
	char		*ptr;
	int			ret;

	if ((ptr = sh_getnenv("PWD", exec->env)))
		ft_strcpy(new_pwd, ptr);
	else if (getcwd(new_pwd, MAXPATHLEN) == NULL)
		return (cd_error(ERR_GETCWD, NULL, e));
	if (!(ptr = ft_strstr(new_pwd, exec->cmd[i + 1])))
		return (cd_error(ERR_NOT_IN_PWD, exec->cmd[i + 1], e));
	if (!cd_change_string(new_pwd, ptr, exec->cmd[i + 1], exec->cmd[i + 2]))
		return (cd_error(ERR_NAME_TOO_LONG, NULL, e));
	if (chdir(new_pwd) < 0)
		return (cd_dir_error(new_pwd, new_pwd, e));
	if (sh_putendl_fd(new_pwd, STDOUT_FILENO) < 0)
		return (cd_error(ERR_WRITE, NULL, e));
	ret = cd_change_pwds(new_pwd, exec->env, e);
	return ((ret) ? cd_error(ret, exec->cmd[i], e) : ERR_NO_ERR);
}
