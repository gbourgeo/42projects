/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_kill.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 11:37:07 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/23 11:37:21 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"
#include "ft_dprintf.h"
#include <signal.h>
#include <sys/ioctl.h>

int		job_kill(t_jobs *job, t_s_env *e)
{
	if (job->pgid != 0)
	{
		kill(-job->pgid, SIGTERM);
		kill(-job->pgid, SIGCONT);
	}
	job->status |= JOB_NOTIFIED;
	if (ioctl(e->fd, TIOCSPGRP, &e->pid) < 0)
	{
		ft_dprintf(2, "job [%d] tcsetpgrp failed\n", e->pid);
		return (1);
	}
	return (0);
}
