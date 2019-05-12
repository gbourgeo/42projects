/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_notify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:08:47 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/28 18:10:55 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "ft_printf.h"
#include "signal_intern.h"

void			job_show_status(t_jobs *job, int sig)
{
	if (sig > 0)
		ft_printf("%s: %d\n", sig_err_translate(sig), sig);
	else
		ft_printf("[%d]+  %-22s command\n", job->id,
			process_translate_status(job->m_process->p->status));
}

static void		job_suspended_status(t_jobs *job, int sig)
{
	ft_printf("[%d]+  %-22s %s\n",
			job->id, sig_err_translate(sig), job->cmd_name);
}

int				job_notify(t_jobs *job, t_m_process *m_p)
{
	int		sig;
	int		s_suspended;

	if (job->notify == 1)
		return (0);
	sig = 0;
	if ((s_suspended = job_sig_suspended(job, m_p)) > 0)
	{
		write(1, "\n", 1);
		job_suspended_status(job, s_suspended);
		return (s_suspended + 128);
	}
	else
	{
		sig = job_signaled(job);
		if (sig || (job_suspended(job, m_p) && !job_finished(job, m_p)))
		{
			if (sig != SIGINT && sig != SIGPIPE)
				job_show_status(job, sig);
		}
		return (sig);
	}
}
