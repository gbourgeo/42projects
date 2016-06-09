/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_change_pwds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 09:56:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/06/20 12:37:34 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_main.h"

void			cl_change_pwds(char *pwd, t_envi *cl)
{
	if (cl->oldpwd)
		free(cl->oldpwd);
	cl->oldpwd = cl->lpwd;
	cl->lpwd = ft_strdup(pwd);
}
