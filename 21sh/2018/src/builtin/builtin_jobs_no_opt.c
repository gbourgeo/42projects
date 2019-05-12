/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_jobs_no_opt.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 16:35:49 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/29 16:37:28 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "builtin_jobs.h"
#include "ft_printf.h"
#include "signal_intern.h"

int		jobs_evaluate_sig(t_m_process *m_p)
{
	t_process	*p;

	while (m_p)
	{
		p = m_p->p;
		while (p)
		{
			if (p->s_signal > 0)
				return (p->s_signal);
			p = p->next;
		}
		m_p = m_p->next;
	}
	return (0);
}

int		jobs_evaluate_ended_status(t_m_process *m_p)
{
	t_process	*p;

	while (m_p)
	{
		p = m_p->p;
		while (p)
		{
			if (p->status != STATUS_FINISHED)
				return (p->status);
			p = p->next;
		}
		m_p = m_p->next;
	}
	return (STATUS_FINISHED);
}

void	job_no_opt(const t_jobs *job)
{
	int			status;

	ft_printf("[%d]", job->id);
	if (job->status & JOB_LAST)
		ft_printf("+  ");
	else if (job->status & JOB_MINUS)
		ft_printf("-  ");
	else
		ft_printf("   ");
	if ((status = jobs_evaluate_sig(job->m_process)))
		ft_printf("%-22s", sig_err_translate(status));
	else if ((status = jobs_evaluate_ended_status(job->m_process)))
		ft_printf("%-22s", process_translate_status(status));
	ft_printf("%s", job->cmd_name);
	ft_printf("\n");
}
