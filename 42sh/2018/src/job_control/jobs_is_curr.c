/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_is_curr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:23:01 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/29 16:36:13 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

int		job_is_curr(t_jobs *job, t_execute *exec)
{
	t_m_process		*m_p;
	t_process		*p;

	m_p = job->m_process;
	while (m_p)
	{
		p = m_p->p;
		while (p)
		{
			if (p->exec == exec)
				return (1);
			p = p->next;
		}
		m_p = m_p->next;
	}
	return (0);
}
