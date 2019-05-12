/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_foreground.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:36:31 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/29 10:12:37 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <sys/ioctl.h>
#include "libft.h"
#include "ft_dprintf.h"
#include "job_control.h"
#include "signal_intern.h"

static int	job_fg_cont(t_jobs *job, t_s_env *e, int cont)
{
	job->status |= JOB_FOREGROUND;
	job->status |= JOB_NOTIFIED;
	if (cont)
	{
		tcsetattr(0, TCSADRAIN, &job->save);
		job->notify = 1;
		if (kill(-job->pgid, SIGCONT) < 0)
		{
			ft_dprintf(2, "failed to continue job [%d]\n", job->pgid);
			return (job_kill(job, e));
		}
	}
	return (0);
}

static void	job_give_status(t_jobs *job)
{
	if (job->prev)
	{
		job->status |= JOB_LAST;
		job->prev->status &= ~JOB_LAST;
		job->prev->status |= JOB_MINUS;
		if (job->prev->prev)
			job->prev->prev->status &= ~JOB_MINUS;
	}
	else
		job->status |= JOB_LAST;
}

int			job_foreground(t_jobs *job, t_m_process *m_p, t_s_env *e, int cont)
{
	int		status;

	job_give_status(job);
	if ((status = job_fg_cont(job, e, cont)) != 0)
		return (status);
	if (job->pgid && ioctl(e->fd, TIOCSPGRP, &job->pgid) < 0)
	{
		ft_dprintf(2, "job [%d] tcsetpgrp failed\n", job->pgid);
		return (job_kill(job, e));
	}
	status = job_wait(job, m_p, e);
	if (ioctl(e->fd, TIOCSPGRP, &e->pid) < 0)
	{
		ft_dprintf(2, "job [%d] tcsetpgrp failed\n", job->pgid);
		return (job_kill(job, e));
	}
	tcsetattr(0, TCSADRAIN, &e->save);
	return (*e->ret);
}
