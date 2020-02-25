/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 04:51:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/24 14:21:44 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "cl_main.h"

int				cl_init(char **environ, t_env *env)
{
	char		*ptr;

	if ((ptr = ft_getenv("HOME=", environ)))
	{
		ft_strdel(&env->home);
		env->home = ptr;
	}
	if (!(env->pwd = ft_getenv("PWD=", environ)))
		env->pwd = getcwd(NULL, 0);
	if (!(env->oldpwd = ft_getenv("OLDPWD=", environ)))
		env->oldpwd = getcwd(NULL, 0);
	if (!env->home || !env->pwd || !env->oldpwd)
		return (ERR_MALLOC);
	return (IS_OK);
}
