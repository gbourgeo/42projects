/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_wait.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:33:20 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/28 22:29:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

int		job_wait(t_jobs *job, t_m_process *m_p, t_s_env *e)
{
	t_process	*p;

	while (1)
	{
		p = m_p->p;
		while (p)
		{
			process_status(job, m_p, p, e);
			p = p->next;
		}
		if (job_suspended(job, m_p))
			break ;
		if (job_finished(job, m_p))
			break ;
	}
	return (job_notify(job, job->m_process));
}
