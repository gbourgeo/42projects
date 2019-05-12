/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_dup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaffier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 16:57:39 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/27 16:01:45 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "redirection.h"
#include "shell_env.h"

static int		dup2_and_close(t_process *p, int from, int to)
{
	if (to != from)
	{
		if (to == -1 && from > 0)
			close(from);
		else
		{
			dup2(to, from);
			if (!(to == STDERR_FILENO && from == STDOUT_FILENO)
					&& !(to == STDOUT_FILENO && from == STDERR_FILENO))
				if (to > 3 && to != -1)
					close(to);
		}
	}
	if (from == STDIN_FILENO)
	{
		if (p->pipe[0] != -1)
			close(p->pipe[0]);
		if (p->pipe[1] != -1)
			close(p->pipe[1]);
	}
	return (1);
}

void			command_setup(t_process *p)
{
	if (p->fds[1] == STDERR_FILENO)
	{
		dup2_and_close(p, STDERR_FILENO, p->fds[2]);
		dup2_and_close(p, STDOUT_FILENO, p->fds[1]);
	}
	else
	{
		dup2_and_close(p, STDOUT_FILENO, p->fds[1]);
		dup2_and_close(p, STDERR_FILENO, p->fds[2]);
	}
	dup2_and_close(p, STDIN_FILENO, p->fds[0]);
}

void			command_rd_forked(t_redirection *r, t_s_env *e)
{
	while (r)
	{
		if (redirection(&r, e))
			exit(1);
		r = r->next;
	}
}
