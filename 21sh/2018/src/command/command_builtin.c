/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 23:11:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/27 16:01:04 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_lib.h"
#include "command.h"
#include "command_error.h"
#include "shell_lib.h"
#include "job_control.h"

int				command_builtin(t_builtin builtin, t_jobs *job,
		t_process *p, t_s_env *e)
{
	int			error;
	t_execute	*exec;

	job->status |= JOB_BUILTIN_INTERN;
	exec = (t_execute *)p->exec;
	if ((error = command_redirect(exec->fds, exec->redirection)) != ERR_OK)
		command_error(e->progname, error, NULL, e);
	else
		*e->ret = builtin(exec, e);
	if ((error = command_restore_fds(exec->fds)) != ERR_OK)
		command_error(e->progname, error, NULL, e);
	job->status |= JOB_NOTIFIED;
	return (ERR_OK);
}
