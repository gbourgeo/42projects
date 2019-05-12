/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_finished.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:38:04 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/28 22:28:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

static int	job_forked_finished(t_jobs *job)
{
	t_process	*p;

	p = (t_process *)job->job_forked;
	return (p->status != STATUS_FINISHED ? 0 : 1);
}

int			job_finished(t_jobs *job, t_m_process *m_p)
{
	t_process	*p;

	if (job->status & JOB_FORKED)
		return (job_forked_finished(job));
	p = m_p->p;
	while (p)
	{
		if (p->status != STATUS_FINISHED)
			return (0);
		p = p->next;
	}
	return (1);
}
