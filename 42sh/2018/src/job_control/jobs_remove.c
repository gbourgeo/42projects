/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_remove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:17:32 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/29 16:46:38 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

static void		free_proc(t_process *proc)
{
	if (proc)
	{
		command_free((t_execute *)proc->exec, NULL);
		proc->exec = NULL;
		free_proc(proc->next);
		free(proc);
	}
}

static void		remove_m_proc(t_m_process *p)
{
	if (p)
	{
		free_proc(p->p);
		remove_m_proc(p->next);
		free(p);
	}
}

static void		remove_job(t_jobs **job, t_jobs *node)
{
	if (*job == NULL || node == NULL)
		return ;
	if (*job == node)
		*job = node->next;
	if (node->next != NULL)
		node->next->prev = node->prev;
	if (node->prev != NULL)
		node->prev->next = node->next;
	remove_m_proc(node->m_process);
	free(node->cmd_name);
	free(node);
	node = NULL;
}

void			jobs_remove(t_jobs **jobs, int n)
{
	t_jobs	*curr;
	t_jobs	*save;

	if (!jobs || !*jobs)
		return ;
	curr = *jobs;
	while (curr)
	{
		if (curr->status & JOB_CURR)
			curr->status &= ~JOB_CURR;
		save = curr->next;
		if (n == 0 || (curr->status & JOB_NOTIFIED))
		{
			remove_job(jobs, curr);
			curr = save;
		}
		else
			curr = curr->next;
	}
}
