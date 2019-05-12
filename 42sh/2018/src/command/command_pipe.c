/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 06:58:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/29 16:55:08 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "libft.h"
#include "ft_dprintf.h"
#include "command.h"
#include "shell_lib.h"
#include "shell_env.h"
#include "job_control.h"
#include "command_error.h"

void		close_unexpected_fd(int *fds)
{
	if (fds[2] != STDIN_FILENO && fds[2] != STDOUT_FILENO
			&& fds[2] != STDERR_FILENO)
		if (fds[2] != -1)
			close(fds[2]);
	if (fds[3] != STDIN_FILENO && fds[3] != STDOUT_FILENO
			&& fds[3] != STDERR_FILENO)
		if (fds[3] != -1)
			close(fds[3]);
	if (fds[4] != STDIN_FILENO && fds[4] != STDOUT_FILENO
			&& fds[4] != STDERR_FILENO)
		if (fds[4] != -1)
			close(fds[4]);
}

int			command_pipe_dup(t_jobs *job, t_process *p, t_s_env *e, int *fds)
{
	fds[FD_STDERR] = p->fds[2];
	if (p->next)
	{
		if (pipe(fds) < 0)
			return (command_error(e->progname, 10, NULL, e));
		fds[3] = fds[FD_PIPE_OUT];
	}
	else
		fds[3] = p->fds[1];
	p->pipe[0] = fds[0];
	p->pipe[1] = fds[1];
	if (p->fds[0] == STDIN_FILENO)
		p->fds[0] = fds[2];
	if (p->fds[1] == STDOUT_FILENO)
		p->fds[1] = fds[3];
	return (command_check(job, p, e));
}
