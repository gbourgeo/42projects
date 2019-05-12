/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jobs_no_arg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 11:02:15 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/29 16:38:39 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "builtin_jobs.h"

int		jobs_no_arg(const t_jobs *jobs, t_execute *exec, const int *opts)
{
	update_jobs(jobs);
	while (jobs)
	{
		if (job_is_curr((t_jobs *)jobs, exec))
			;
		else if (*opts & JOB_OPT_P)
			job_opt_p(jobs);
		else if (*opts & JOB_OPT_L)
			job_opt_l(jobs);
		else
			job_no_opt(jobs);
		jobs = jobs->next;
	}
	return (0);
}

int		jobs_spe_arg(t_execute *exec, t_s_env *e, int i, const int *opts)
{
	int			err;
	char		**cmd;
	t_jobs		*curr;

	err = 0;
	cmd = exec->cmd;
	while (cmd[i])
	{
		if (!(curr = jobs_expansions(cmd[i], exec, e)))
		{
			jobs_error(2, cmd[i], e);
			err = 1;
		}
		else if (curr && *opts & JOB_OPT_P)
			job_opt_p(curr);
		else if (*opts & JOB_OPT_L)
			job_opt_l(curr);
		else
			job_no_opt(curr);
		i++;
	}
	return (err);
}
