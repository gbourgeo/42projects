/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 15:17:20 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/20 10:08:52 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

t_jobs		*job_by_id(int id, t_jobs *jobs)
{
	while (jobs)
	{
		if (jobs->id == id)
			return (jobs);
		jobs = jobs->next;
	}
	return (jobs);
}

t_jobs		*job_by_pid(t_jobs *jobs, pid_t pid)
{
	t_process	*curr;

	while (jobs)
	{
		if (pid == jobs->pgid)
			return (jobs);
		curr = jobs->m_process->p;
		while (curr)
		{
			if (curr->pid == pid)
				return (jobs);
			curr = curr->next;
		}
		jobs = jobs->next;
	}
	return (NULL);
}
