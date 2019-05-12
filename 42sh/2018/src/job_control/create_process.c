/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:39:19 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/27 21:51:15 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "shell_env.h"
#include "shell_lib.h"

static void	insert_process(t_jobs *job, t_process *new)
{
	t_m_process	*m_p;
	t_process	*curr;

	m_p = job->curr;
	curr = m_p->p;
	if (!curr)
		m_p->p = new;
	else
	{
		while (curr->next != NULL)
			curr = curr->next;
		new->pid = -1;
		curr->next = new;
	}
}

int			create_process(t_s_env *e, t_execute *exec, int type)
{
	t_jobs		*job;
	t_process	*new;

	if (!(new = ft_memalloc(sizeof(t_process))))
		return (0);
	new->exec = exec;
	new->type = type;
	new->fds[0] = STDIN_FILENO;
	new->fds[1] = STDOUT_FILENO;
	new->fds[2] = STDERR_FILENO;
	new->pipe[0] = -1;
	new->pipe[1] = -1;
	job = job_by_id(e->job_id, e->jobs);
	insert_process(job, new);
	return (1);
}
