/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 22:27:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/17 22:31:57 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

void			sv_free_env(t_env *env)
{
	if (env->path)
		free(env->path);
	if (env->home)
		free(env->home);
	// if (info->lpwd)
	// 	free(info->lpwd);
	// if (info->oldpwd)
	// 	free(info->oldpwd);
	// if (info->user)
	// 	free(info->user);
	// if (info->pwd)
	// 	free(info->pwd);
}
