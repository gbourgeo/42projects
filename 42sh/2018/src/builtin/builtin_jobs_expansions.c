/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jobs_expansions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 11:20:18 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/28 17:52:02 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "builtin_jobs.h"

static t_jobs		*jobs_get_current(t_jobs *jobs, t_execute *exec)
{
	while (jobs)
	{
		if (jobs->status & JOB_LAST)
		{
			if (!(jobs->m_process->p->exec == exec))
				return (jobs);
		}
		jobs = jobs->next;
	}
	return (NULL);
}

static t_jobs		*jobs_get_prev(t_jobs *jobs)
{
	while (jobs)
	{
		if (jobs->status & JOB_MINUS)
			return (jobs);
		jobs = jobs->next;
	}
	return (NULL);
}

static t_jobs		*jobs_get_arg(t_jobs *jobs,
		const char *arg, t_execute *exec)
{
	int		id;

	id = ft_atoi(arg);
	while (jobs)
	{
		if (jobs->id == id)
			if (!(jobs->m_process->p->exec == exec))
				return (jobs);
		jobs = jobs->next;
	}
	return (NULL);
}

t_jobs				*jobs_expansions(const char *arg,
		t_execute *exec, t_s_env *e)
{
	if (arg[0] == '%')
	{
		if (!arg[1] || arg[1] == '%' || arg[1] == '+')
			return (jobs_get_current(e->jobs, exec));
		if (arg[1] == '-')
			return (jobs_get_prev(e->jobs));
		if (arg[1])
			return (jobs_get_arg(e->jobs, arg + 1, exec));
	}
	return (jobs_get_arg(e->jobs, arg, exec));
}
