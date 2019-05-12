/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_signaled.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:10:02 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/28 22:32:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

static int	job_forked_sig(t_jobs *job)
{
	t_process	*p;

	p = (t_process *)job->job_forked;
	return (p->s_signal > 0 ? p->s_signal : 0);
}

int			job_signaled(t_jobs *job)
{
	t_process	*p;
	t_m_process	*m_p;

	if (job->status & JOB_FORKED)
		return (job_forked_sig(job));
	m_p = job->m_process;
	while (m_p)
	{
		p = m_p->p;
		while (p)
		{
			if (p->s_signal > 0)
				return (p->s_signal);
			p = p->next;
		}
		m_p = m_p->next;
	}
	return (0);
}
