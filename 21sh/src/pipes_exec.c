/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 05:23:38 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/01 11:49:10 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		pipe_child(int *fd, char ***cmd, int *p, t_env *e)
{
	dup2(*fd, 0);
	if (*(cmd + 1) != NULL)
		dup2(p[1], 1);
	close(p[0]);
	check_and_exec(*cmd, e);
	close(p[1]);
	exit(e->ret);
}

static void		pipe_father(pid_t pid, int *p, t_env *e)
{
	waitpid(pid, &e->ret, 0);
	if (e->ret == 512)
	{
		e->ret = 130;
		ft_putchar('\n');
	}
	close(p[1]);
}

void			pipes_loop(t_pipe pi, t_env *e)
{
	int			p[2];
	pid_t		pid;
	int			fd;

	e->ret = 1;
	init_sigint(1);
	while (*pi.cmd != NULL && e->ret != 130)
	{
		if (pipe(p) == -1)
			return (ft_putendl_fd("21sh: pipe() failure.", 2));
		if ((pid = fork()) == -1)
			return (ft_putendl_fd("21sh: fork() failure.", 2));
		else if (pid == 0)
			pipe_child(&fd, pi.cmd, p, e);
		else
			pipe_father(pid, p, e);
		fd = p[0];
		pi.cmd++;
	}
	init_sigint(0);
}
