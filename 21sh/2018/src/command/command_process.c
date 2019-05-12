/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:58:37 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/28 15:35:31 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_env.h"
#include "job_control.h"
#include "ft_dprintf.h"

void			command_process(pid_t pid, pid_t s_pid,
		t_jobs *job, t_process *p)
{
	p->status = STATUS_RUNNING;
	if (job->pgid == 0 || job->pgid == s_pid)
		job->pgid = pid;
	if (setpgid(p->pid, job->pgid) < 0)
		ft_dprintf(2, "Setpgid failed %s\n", __func__);
}
