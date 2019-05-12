/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 21:33:49 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/29 01:49:47 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

static void	add_job(t_jobs *jobs, t_jobs *new)
{
	if (jobs == NULL || new == NULL)
		return ;
	while (jobs->next)
		jobs = jobs->next;
	new->id = jobs->id + 1;
	jobs->next = new;
	new->prev = jobs;
}

t_jobs		*job_insert(t_s_env *e)
{
	t_jobs		*job;

	job = NULL;
	if (!(job = ft_memalloc(sizeof(t_jobs))))
		return (0);
	job->id = 1;
	job->pgid = e->pid;
	job->save = e->save;
	if (!e->jobs)
		e->jobs = job;
	else
		add_job(e->jobs, job);
	e->job_id = job->id;
	return (job);
}
