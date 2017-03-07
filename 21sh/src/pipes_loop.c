/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 05:23:38 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/07 19:24:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		pipe_fork(char **args, t_env *e)
{
	char		*path;

	if ((path = get_path(args, e)) != NULL)
	{
		e->ret = execve(path, args, e->env);
		ft_putendl_fd("21sh: check your arguments.", 2);
	}
	else
		ft_put2endl_fd("21sh: command not found: ", args[0], 2);
	if (path)
		free(path);
	exit(e->ret);
}

static void		pipe_exec(char **command, t_env *e, int fork)
{
	static char	*builtins[] = { BUILTINS };
	static void	(*function[])(char **, t_env *) = { FUNCTION };
	char		*path;
	int			i;

	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(*command, builtins[i]) == 0)
		{
			function[i](command, e);
			return ;
		}
		i++;
	}
	if (!fork)
		pipe_fork(command, e);
	else
	{
		path = fork_function(command, e);
		if (path)
			free(path);
	}
}

static void		pipe_error(char *err, int p, t_env *e)
{
	if (err)
	{
		ft_putstr_fd("21sh: ", 2);
		ft_putendl_fd(err, 2);
		e->ret = 1;
	}
	else if (e->ret == 512)
	{
		ft_putchar('\n');
		e->ret = 130;
	}
	if (p > -1)
		close(p);
	init_sigint(0);
	redefine_term();
}

void			pipes_loop(t_pipe pi, t_env *e, long tot)
{
	int			p[2];
	pid_t		pid;
	char		*cat[3];

	if (*(pi.table + tot + pi.redir) && **(pi.table + tot + pi.redir) == '|')
	{

		if (pipe(p) == -1)
			return (pipe_error("pipe() failed.", -1, e));
		if ((pid = fork()) < 0)
			return (pipe_error("fork() failed.", -1, e));
		if (pid == 0)
		{
			if (pi.pipe)
			{
				dup2(pi.pipe, STDIN_FILENO);
				close(pi.pipe);
				pi.pipe = 0;
			}
			close(p[0]);
			dup2(p[1], STDOUT_FILENO);
			close(p[1]);
			pipe_exec(*(pi.cmd + tot), e, 0);
		}
		else
		{
			close(p[1]);
			waitpid(pid, &e->ret, 0);
			if (e->ret)
				return (pipe_error(NULL, p[0], e));
			tot += pi.redir + 1;
			pi.redir = 0;
			if (*(pi.table + tot + pi.redir))
			{
				pi.pipe = p[0];
				pipes_loop(pi, e, tot);
				close(p[0]);
			}
			else
			{
				dup2(p[0], STDIN_FILENO);
				close(p[0]);
				pipe_exec(*(pi.cmd + tot + pi.redir), e, 1);
				dup2(1, STDIN_FILENO);
			}
			tot += pi.redir + 1;
			pi.redir = 0;
		}
	}
	else if (*(pi.table + tot + pi.redir) && **(pi.table + tot + pi.redir) == '<')
	{

		if (pipe(p) == -1)
			return (pipe_error("pipe() failed.", -1, e));
		if ((pid = fork()) < 0)
			return (pipe_error("fork() failed.", -1, e));
		if (pid == 0)
		{
			if (pi.pipe)
			{
				dup2(pi.pipe, STDIN_FILENO);
				close(pi.pipe);
				pi.pipe = 0;
			}
			close(p[0]);
			dup2(p[1], STDOUT_FILENO);
			close(p[1]);
			int i = 0;
			while (*(pi.table + tot + i) && **(pi.table + tot + i) == '<')
				i++;
			char *more[i + 1];
			int j = 0;
			more[j] = "more";
			while (*(pi.table + tot + j) && **(pi.table + tot + j) == '<')
			{
				more[j + 1] = **(pi.cmd + tot + j + 1);
				j++;
			}
			more[j + 1] = NULL;
			pipe_exec(more, e, 0);			
		}
		else
		{
			close(p[1]);
			waitpid(pid, &e->ret, 0);
			if (e->ret)
				return (pipe_error(NULL, p[0], e));
			while (*(pi.table + tot + pi.redir) && **(pi.table + tot + pi.redir) == '<')
				pi.redir++;
			if (*(pi.table + tot + pi.redir))
			{
				pi.pipe = p[0];
				pipes_loop(pi, e, tot);
				close(p[0]);
			}
			else
			{
				dup2(p[0], STDIN_FILENO);
				close(p[0]);
				if (**(pi.cmd + tot))
					pipe_exec(*(pi.cmd + tot), e, 1);
				else
				{
					cat[0] = "cat";
					pipe_exec(cat, e, 1);
				}
				dup2(1, STDIN_FILENO);
			}
		}
	}
	else if (*(pi.table + tot + pi.redir) && **(pi.table + tot + pi.redir) == '>')
	{

		if ((pid = fork()) < 0)
			return (pipe_error("fork() failed.", -1, e));
		if (pid == 0)
		{
			if (pi.pipe)
			{
				dup2(pi.pipe, STDIN_FILENO);
				close(pi.pipe);
				pi.pipe = 0;
			}
			pi.redir++;
			dup2(*(pi.fds + tot + pi.redir), STDOUT_FILENO);
			close(*(pi.fds + tot + pi.redir));
			if (tot + pi.redir - 2 >= 0 && **(pi.table + tot + pi.redir - 2) == '>')
			{
				cat[0] = "cat";
				cat[1] = **(pi.cmd + tot + pi.redir - 1);
				pipe_exec(cat, e, 0);
			}
			else if (**(pi.cmd + tot))
				pipe_exec(*(pi.cmd + tot), e, 0);
			else
			{
				cat[0] = "cat";
				pipe_exec(cat, e, 0);
			}
		}
		else
		{
			waitpid(pid, &e->ret, 0);
			if (e->ret)
				return (pipe_error(NULL, p[0], e));
			pi.redir++;
			if (*(pi.table + tot + pi.redir))
			{
				pi.pipe = *(pi.fds + tot + pi.redir);
				pipes_loop(pi, e, tot);
			}
		}
	}
}
