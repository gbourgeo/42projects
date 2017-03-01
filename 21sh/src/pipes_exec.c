/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 05:23:38 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/01 14:09:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		pipe_child(t_pipe *pi, int *p, t_env *e)
{
	if (*pi->table && **pi->table == '<')
	{
		close(STDIN_FILENO);
		dup2(*(pi->fds + 1), STDIN_FILENO);
		close(*(pi->fds + 1));
	}
	else
	{
		close(STDIN_FILENO);
		dup2(pi->fd, STDIN_FILENO);
		close(pi->fd);
	}
	if (*pi->table && **pi->table == '>')
	{
		close(STDOUT_FILENO);
		dup2(*(pi->fds + 1), STDOUT_FILENO);
		close(*(pi->fds + 1));
	}
	else if (*(pi->cmd + 1) != NULL)
	{
		close(STDOUT_FILENO);
		dup2(p[1], STDOUT_FILENO);
		close(p[1]);
	}
	if (*pi->fds == STDOUT_FILENO)
		check_and_exec(*pi->cmd, e);
	exit(e->ret);
}

static void		pipe_father(pid_t pid, int *p, t_env *e)
{
	close(p[1]);
	waitpid(pid, &e->ret, 0);
	if (e->ret == 512)
	{
		e->ret = 130;
		ft_putchar('\n');
	}
}

void			pipes_loop(t_pipe pi, t_env *e)
{
	int			p[2];
	pid_t		pid;

	e->ret = 1;
	pi.fd = 0;
	init_sigint(1);
	while (*pi.cmd != NULL && e->ret != 130)
	{
		if (pipe(p) == -1)
			return (ft_putendl_fd("21sh: pipe() failure.", 2));
		if ((pid = fork()) == -1)
			return (ft_putendl_fd("21sh: fork() failure.", 2));
		else if (pid == 0)
			pipe_child(&pi, p, e);
		else
			pipe_father(pid, p, e);
		pi.fd = p[0];
		pi.cmd++;
		pi.table++;
		pi.fds++;
	}
	init_sigint(0);
}
