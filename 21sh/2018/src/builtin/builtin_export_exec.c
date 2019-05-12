/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_exec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 18:34:19 by tsisadag          #+#    #+#             */
/*   Updated: 2019/04/29 16:08:25 by tsisadag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtins.h"
#include "builtin_export.h"
#include "shell_lib.h"

/*
** adding local should check if its in exported
** adding public should check if its exported
*/

int		exec_export(char *arg, t_s_env *e)
{
	if (!valid_id(arg))
		return (1);
	if (!is_local(arg, e->private_env)
	&& !is_public(arg, e->public_env) && (!has_value(arg)))
	{
		if (!is_exported(arg, e->exported_env))
			add_exported(arg, e);
	}
	else
		change_public_env(arg, e);
	return (0);
}

void	change_public_env(char *arg, t_s_env *e)
{
	if (is_public(arg, e->public_env))
	{
		if (arg[var_name_len(arg)] != '\0')
			change_public(arg, e);
	}
	else
	{
		add_public(arg, e);
		if (is_local(arg, e->private_env))
			delete_local(arg, e, 0, 0);
		if (is_exported(arg, e->exported_env))
			delete_exported(arg, e, 0, 0);
	}
}
