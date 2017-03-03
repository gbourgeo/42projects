/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 05:23:38 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/03 16:43:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		pipe_child(t_pipe *pi, int *p, t_env *e)
{
	int			tot;

	tot = pi->pipe + pi->redir;
	if (pi->fd == -1)
		pi->fd = p[0];
	close(STDIN_FILENO);
	dup2(pi->fd, STDIN_FILENO);
	close(pi->fd);
	if (*(pi->cmd + tot + 1) != NULL)
	{
		close(STDOUT_FILENO);
		dup2(p[1], STDOUT_FILENO);
		close(p[1]);
	}
	if (tot == 0 || **(pi->table + tot - 1) == '|')
		check_and_exec(*(pi->cmd + tot), e);
/* 	else */
/* 		check_and_exec(*(pi->cmd + pi->last_pipe), e); */
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
	int			tot;
	pid_t		pid;

	tot = pi.pipe + pi.redir;
	if (e->ret != 130)
	{
		if ((*(pi.table + tot) == NULL && **(pi.table + tot - 1) == '|') || **(pi.table + tot) == '|')
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
			pi.pipe++;
			if (*(pi.table + tot))
			{
				pi.last_pipe = tot + 1;
				pipes_loop(pi, e);
			}
		}
		else if (*(pi.table + tot) && **(pi.table + tot) == '>')
		{
			if ((pid = fork()) == -1)
				return (ft_putendl_fd("21sh: fork() failure.", 2));
			else if (pid == 0)
			{
				if (pi.fd > -1)
				{
					close(STDIN_FILENO);
					dup2(pi.fd, STDIN_FILENO);
					close(pi.fd);
				}
				close(STDOUT_FILENO);
				dup2(*(pi.fds + tot + 1), STDOUT_FILENO);
				close(*(pi.fds + tot + 1));
				check_and_exec(*(pi.cmd + pi.last_pipe), e);
				exit(e->ret);
			}
			else
				waitpid(pid, &e->ret, 0);
//			if (pi.fd == -1)
			pi.fd = *(pi.fds + tot + 1);
			pi.redir++;
			pipes_loop(pi, e);
		}
		else if (*(pi.table + tot) && **(pi.table + tot) == '<')
		{
			if ((pid = fork()) == -1)
				return (ft_putendl_fd("21sh: fork() failure.", 2));
			else if (pid == 0)
			{
				close(STDIN_FILENO);
				dup2(*(pi.fds + tot + 1), STDIN_FILENO);
				close(*(pi.fds + tot + 1));
				if (*(pi.table + tot + 1) && **(pi.table + tot + 1) != '<')
				{
					close(STDOUT_FILENO);
					dup2(*(pi.fds + tot + 2), STDOUT_FILENO);
					close(*(pi.fds + tot + 2));
				}
				check_and_exec(*(pi.cmd + pi.last_pipe), e);
				exit(e->ret);
			}
			else
				waitpid(pid, &e->ret, 0);
			pi.redir++;
			pi.fd = *(pi.fds + tot + 1);
			pipes_loop(pi, e);
		}
	}
}
