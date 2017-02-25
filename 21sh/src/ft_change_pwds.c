/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_pwds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/15 20:44:42 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/25 03:22:50 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void		ft_change_pwds(char *pwd, t_env *e)
{
	char		**tmp;

	e->ret = 1;
	if ((tmp = ft_tabnew(4)) == NULL)
		return (ft_putendl_fd("21sh: malloc failed", 2));
	tmp[0] = "setenv";
	tmp[1] = "OLDPWD";
	tmp[2] = ft_getenv("PWD", e->env);
	tmp[3] = NULL;
	ft_setenv(tmp, e);
	tmp[1] = "PWD";
	tmp[2] = pwd;
	ft_setenv(tmp, e);
	free(tmp);
}
