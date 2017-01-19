/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_pwds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/15 20:44:42 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/09 16:08:55 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		ft_change_pwds(char *pwd)
{
	char		**tmp;

	if ((tmp = (char**)malloc(sizeof(char*) * 4)) != NULL)
	{
		tmp[0] = ft_strdup("setenv");
		tmp[3] = 0;
		if (ft_getenv("OLDPWD", e.env))
		{
			tmp[1] = ft_strdup("OLDPWD");
			tmp[2] = ft_getenv("PWD", e.env);
			e.ret = ft_setenv(tmp);
			free(tmp[1]);
		}
		if (ft_getenv("PWD", e.env))
		{
			tmp[1] = ft_strdup("PWD");
			tmp[2] = ft_strdup(pwd);
			e.ret = ft_setenv(tmp);
		}
		ft_free(&tmp);
	}
}
