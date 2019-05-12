/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_jobs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:57:35 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/29 16:55:15 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"
#include "job_control.h"
#include "command.h"
#include "operator_types.h"
#include "command_error.h"

static void		set_fds(int *fds, int size)
{
	int		i;

	i = -1;
	while (++i < size)
		fds[i] = -1;
}

static int		launch_m_process(t_jobs *job, t_m_process *m_p, t_s_env *e)
{
	int			fds[5];
	int			ret;
	t_process	*curr;

	set_fds(fds, 5);
	curr = m_p->p;
	ret = 0;
	job->pgid = 0;
	while (curr)
	{
		if ((ret = command_pipe_dup(job, curr, e, fds)) != 0)
			return (ret);
		close_unexpected_fd(fds);
		fds[FD_STDIN] = fds[FD_PIPE_IN];
		m_p->ret = curr->exit_status;
		curr = curr->next;
	}
	return (0);
}

static int		command_launch_mp_b(t_jobs *job, t_s_env *e)
{
	int			ret;
	t_m_process	*m_p;

	ret = 0;
	m_p = job->m_process;
	while (m_p)
	{
		if (m_p->type == OR_IF_VALUE && *e->ret == 0)
		{
			m_p = m_p->next;
			continue ;
		}
		else if (m_p->type == AND_IF_VALUE && *e->ret != 0)
		{
			m_p = m_p->next;
			continue ;
		}
		if ((ret = launch_m_process(job, m_p, e)) != 0)
			return (ret);
		if ((ret = job_wait(job, m_p, e)) != 0)
			return (ret);
		ret = m_p->ret;
		m_p = m_p->next;
	}
	return (0);
}

int				command_mprocess_background(t_jobs *job, t_s_env *e)
{
	int			error;

	error = 0;
	if ((job->pgid = fork()) == 0)
	{
		error = command_launch_mp_b(job, e);
		exit(EXIT_FAILURE);
	}
	else if (job->pgid < 0)
		error = command_error(e->progname, ERR_FORK, NULL, e);
	command_job_wait(job, job->m_process, e);
	job->status |= JOB_FORKED;
	return (error);
}

int				command_job(t_jobs *job, t_s_env *e)
{
	t_m_process	*m_p;
	int			ret;

	if (job->m_process->next && job->foreground == 1)
		return (command_mprocess_background(job, e));
	m_p = job->m_process;
	while (m_p)
	{
		if (m_p->type == OR_IF_VALUE && *e->ret == 0)
		{
			m_p = m_p->next;
			continue ;
		}
		else if (m_p->type == AND_IF_VALUE && *e->ret != 0)
		{
			m_p = m_p->next;
			continue ;
		}
		if ((ret = launch_m_process(job, m_p, e)) != 0
				&& m_p->p->next == NULL)
			return (ret);
		command_job_wait(job, m_p, e);
		m_p = m_p->next;
	}
	return (0);
}
