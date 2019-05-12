/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_update.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:44:17 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/29 01:54:39 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "builtin_jobs.h"

int				job_ch_suspended(t_jobs *job)
{
	t_m_process	*m_p;

	m_p = job->m_process;
	while (m_p)
	{
		if (job_suspended(job, m_p))
			return (job_notify(job, m_p));
		m_p = m_p->next;
	}
	return (1);
}

int				jobs_notify(t_jobs *jobs, t_m_process *m_p)
{
	while (jobs)
	{
		if (job_finished(jobs, m_p) && !(jobs->status & JOB_CURR))
		{
			jobs->status |= JOB_NOTIFIED;
			job_no_opt(jobs);
		}
		else if (job_ch_suspended(jobs))
		{
			;
		}
		jobs = jobs->next;
	}
	return (1);
}
