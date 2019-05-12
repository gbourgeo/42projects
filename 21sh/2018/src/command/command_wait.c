/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_wait.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 09:43:12 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/28 22:27:49 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_env.h"
#include "job_control.h"
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include "command.h"
#include "signal_intern.h"

int		command_ret(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSTOPPED(status))
		return (WSTOPSIG(status) + 128);
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (0);
}

int		command_job_wait(t_jobs *job, t_m_process *m_p, t_s_env *e)
{
	int		status;

	if (!e->interactive)
	{
		job->foreground = 0;
		job_wait(job, m_p, e);
	}
	else if (job->status & JOB_BUILTIN_INTERN)
	{
		job->status &= ~JOB_BUILTIN_INTERN;
		return (0);
	}
	else if (job->foreground == 1)
		return (job_background(job, m_p, e, 0));
	else
	{
		if ((status = job_foreground(job, m_p, e, 0)) != 0)
			return (status);
	}
	return (0);
}
