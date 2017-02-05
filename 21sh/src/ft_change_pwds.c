/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_pwds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/15 20:44:42 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/04 22:03:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		ft_change_pwds(char *pwd, char ***env)
{
	char		**tmp;

	if ((tmp = (char**)malloc(sizeof(char*) * 4)) != NULL)
	{
		tmp[0] = ft_strdup("setenv");
		tmp[3] = 0;
		if (ft_getenv("OLDPWD", *env))
		{
			tmp[1] = ft_strdup("OLDPWD");
			tmp[2] = ft_getenv("PWD", *env);
			e.ret = ft_setenv(tmp, env);
			free(tmp[1]);
		}
		if (ft_getenv("PWD", *env))
		{
			tmp[1] = ft_strdup("PWD");
			tmp[2] = ft_strdup(pwd);
			e.ret = ft_setenv(tmp, env);
		}
		ft_free(&tmp);
	}
}
