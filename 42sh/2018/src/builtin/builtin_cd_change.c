/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_change.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 06:11:54 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/26 12:41:58 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/param.h>
#include "libft.h"
#include "shell_lib.h"
#include "builtin_cd.h"

int			cd_change_pwds(char *new, char **env, t_s_env *e)
{
	char	get_pwd[MAXPATHLEN];
	char	*pwd;

	sh_unsetenv("OLDPWD", e->public_env);
	sh_unsetenv("OLDPWD", e->private_env);
	if (!(pwd = sh_getnenv("PWD", env)))
	{
		cd_get_path(get_pwd, new);
		sh_setenv("PWD", get_pwd, &e->private_env);
		return (ERR_NO_ERR);
	}
	cd_get_path(get_pwd, pwd);
	sh_setenv("OLDPWD", get_pwd, &e->public_env);
	cd_get_path(get_pwd, new);
	if (sh_getnenv("PWD", e->public_env))
		sh_setenv("PWD", get_pwd, &e->public_env);
	else
		sh_setenv("PWD", get_pwd, &e->private_env);
	return (ERR_NO_ERR);
}
