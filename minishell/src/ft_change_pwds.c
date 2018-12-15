/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_pwds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/15 20:44:42 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/04/05 15:03:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		ft_change_pwds(char *new_pwd, char *old_pwd, t_env *e)
{
	char		**tmp;

	if ((tmp = (char**)malloc(sizeof(char*) * 4)) != NULL)
	{
		tmp[0] = ft_strdup("setenv");
		tmp[3] = 0;
		tmp[1] = ft_strdup("OLDPWD");
		tmp[2] = old_pwd;
		e->ret = ft_setenv(tmp, e);
		ft_freestr(&tmp[1]);
		tmp[1] = ft_strdup("PWD");
		tmp[2] = new_pwd;
		e->ret = ft_setenv(tmp, e);
		ft_freetab(&tmp);
	}
}
