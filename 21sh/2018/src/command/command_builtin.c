/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 23:11:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/15 19:47:53 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_lib.h"
#include "command.h"
#include "command_error.h"

int				command_builtin(t_builtin builtin, t_execute *exec, t_s_env *e)
{
	int			error;

	if ((error = command_redirect(exec->fds, exec->redirection)) != ERR_OK)
		command_error(e->progname, error, NULL, e);
	else
		*e->ret = builtin(exec, e);
	if ((error = command_restore_fds(exec->fds)) != ERR_OK)
		command_error(e->progname, error, NULL, e);
	return (ERR_OK);
}
