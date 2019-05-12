/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_notify_ended.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:49:44 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/29 01:50:45 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "signal_intern.h"
#include "builtin_jobs.h"

static t_m_process	*m_proc_by_pid(t_m_process *begin, pid_t pid)
{
	t_process	*p;

	while (begin)
	{
		p = begin->p;
		while (p)
		{
			if (p->pid == pid)
				return (begin);
			p = p->next;
		}
		begin = begin->next;
	}
	return (begin);
}

static void			jobs_status_set(t_jobs *job, int status, pid_t pid)
{
	t_process	*p;

	p = NULL;
	if (job->status & JOB_FORKED)
	{
		job->job_forked = job->m_process->p;
		process_set_status(job, (t_process *)job->job_forked, status, NULL);
	}
	else
	{
		p = process_by_pid(job->m_process, pid);
		process_set_status(job, p, status, m_proc_by_pid(job->m_process, pid));
	}
}

void				update_jobs(const t_jobs *jobs)
{
	int			status;
	t_jobs		*job;
	pid_t		pid;

	while ((pid = waitpid(WAIT_ANY, &status,
					WCONTINUED | WUNTRACED | WNOHANG)) > 0)
	{
		job = job_by_pid((t_jobs *)jobs, pid);
		jobs_status_set((t_jobs *)job, status, pid);
		if (job_finished(job, job->m_process))
			job->status |= JOB_NOTIFIED;
	}
}

int					jobs_notify_ended(t_jobs *jobs, t_s_env *e)
{
	int			status;
	t_jobs		*job;
	pid_t		pid;

	if (e->g_notif)
	{
		e->g_notif = 0;
		return (1);
	}
	while ((pid = waitpid(WAIT_ANY, &status,
					WCONTINUED | WUNTRACED | WNOHANG)) > 0)
	{
		job = job_by_pid(jobs, pid);
		jobs_status_set(job, status, pid);
		if (job_finished(job, job->m_process))
		{
			job->status |= JOB_NOTIFIED;
			job_no_opt(job);
		}
		else if (job_ch_suspended(job))
		{
			;
		}
	}
	return (1);
}
