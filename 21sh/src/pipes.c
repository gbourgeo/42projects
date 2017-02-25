/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 00:25:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/25 01:40:09 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		pipes_free(char **args, long nb, t_pipe *pi)
{
	long		i;
	long		count;

	i = 0;
	count = 0;
	while (count < nb)
	{
		while (args[i])
			i++;
		args[i] = pi->table[count];
		count++;
	}
	if (pi->table)
		free(pi->table);
	if (pi->cmd)
		free(pi->cmd);
}

static void		pipes_exec(char ***cmd, t_env *e)
{
	int			p[2];
	pid_t		pid;
	int			fd;

	while (*cmd != NULL)
	{
		if (pipe(p) == -1)
			return (ft_putendl_fd("21sh: pipe() failure.", 2));
		if ((pid = fork()) == -1)
			return (ft_putendl_fd("21sh: fork() failure.", 2));
		else if (pid == 0)
		{
			dup2(fd, 0);
			if (*(cmd + 1) != NULL)
				dup2(p[1], 1);
			close(p[0]);
			check_and_exec(*cmd, e);
			exit(e->ret);
		}
		else
		{
			waitpid(pid, &e->ret, 0);
			close(p[1]);
			fd = p[0];
			cmd++;
		}
	}
}

static void		pipes_error(char *str, char **args, long nb, t_pipe *pi)
{
	ft_putstr_fd("21sh: ", 2);
	ft_putendl_fd(str, 2);
	pipes_free(args, nb, pi);
}

static void		pipes_prepare(char **args, t_env *e, long nb)
{
	t_pipe		pi;
	long		i[3];

	if ((pi.table = ft_tabnew(nb + 1)) == NULL)
		return (pipes_error("Insufficient Memory.", args, 0, &pi));
	if ((pi.cmd = (char ***)malloc(sizeof(**pi.cmd) * (nb + 2))) == NULL)
		return (pipes_error("Insufficient Memory.", args, 0, &pi));
	ft_memset(i, 0, sizeof(*i) * 3);
	pi.cmd[i[2]++] = args;
	while (args[i[0]])
	{
		if (ft_strcmp(args[i[0]], "|") == 0)
		{
			pi.table[i[1]++] = args[i[0]];
			args[i[0]] = NULL;
			if (args[i[0] + 1] == NULL)
				return (pipes_error("parse error near `|'", args, i[1], &pi));
			pi.cmd[i[2]++] = &args[i[0] + 1];
		}
		i[0]++;
	}
	pi.cmd[i[2]] = NULL;
	pipes_exec(pi.cmd, e);
	pipes_free(args, nb, &pi);
}

void			pipes_check(char **args, t_env *e)
{
	long		i;
	long		nb;

	i = 0;
	nb = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "|") == 0)
			nb++;
		i++;
	}
	if (nb > 0)
		pipes_prepare(args, e, nb);
	else
		check_and_exec(args, e);
}
