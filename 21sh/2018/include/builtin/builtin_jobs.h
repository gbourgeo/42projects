/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jobs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 16:52:47 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/28 17:56:49 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_JOBS_H
# define BUILTIN_JOBS_H

# include "command.h"

enum
{
	ERR_NO_ERR = 0,
	ERR_INVALID_OPTION,
	ERR_NO_JOB,
};

enum
{
	JOB_OPT_L = 1,
	JOB_OPT_P,
	JOB_OPT_H,
};

t_jobs	*jobs_expansions(const char *arg, t_execute *exec, t_s_env *e);

int		fg_error(int err, char *arg, t_s_env *e);
int		bg_error(int err, char *arg, t_s_env *e);

int		jobs_error(int err, char *arg, t_s_env *e);
int		jobs_no_arg(const t_jobs *jobs, t_execute *exec, const int *opts);
int		jobs_spe_arg(t_execute *exec, t_s_env *e, int i, const int *opts);
int		jobs_evaluate_ended_status(t_m_process *m_p);
int		jobs_evaluate_sig(t_m_process *m_p);

void	job_opt_l(const t_jobs *job);
void	job_opt_p(const t_jobs *job);
void	job_no_opt(const t_jobs *job);

#endif
