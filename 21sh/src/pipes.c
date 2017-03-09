/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 00:25:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/09 21:44:22 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <fcntl.h>
#include <string.h>
#include <errno.h>

static void		pipes_free(char **args, long nb, t_pipe *pi)
{
	long		i;
	long		count;

	i = 0;
	count = 0;
	while (count <= nb)
	{
		if (pi->fds[count] > STDOUT_FILENO)
			close(pi->fds[count]);
		while (args[i])
			i++;
		args[i] = pi->table[count];
		count++;
	}
	if (pi->fds[count] > STDOUT_FILENO)
		close(pi->fds[count]);
	if (pi->table)
		free(pi->table);
	if (pi->cmd)
		free(pi->cmd);
	if (pi->fds)
		free(pi->fds);
}

static void		rework_before(t_pipe *pi, long i, long j)
{
	long		len;

	len = ft_tablen(pi->cmd[i]);
	pi->cmd[i][len] = pi->cmd[i + j + 1][1];
	pi->cmd[i + j + 1][1] = pi->cmd[i + j + 1][0];
	pi->cmd[i + j + 1][0] = NULL;
	pi->cmd[i + j + 1] = &pi->cmd[i + j + 1][1];
	while (j > i)
	{
		pi->cmd[i + j][1] = pi->cmd[i + j][0];
		pi->cmd[i + j][0] = NULL;
		pi->cmd[i + j] = &pi->cmd[i + j][1];
		j--;
	}
}

static void		rework_cmd(t_pipe *pi)
{
	long		i;
	long		j;

	i = 0;
	j = 0;
	while (pi->table[i + j])
	{
		if (pi->table[i + j] && *pi->table[i + j] != '|')
		{
			if (pi->cmd[i + j + 1][1])
				rework_before(pi, i, j);
			else
				j++;
		}
		else if (j == 0)
			i++;
		else
		{
			i += j;
			j = 0;
		}
	}
}

static void		pipes_error(char *str, char **args, long *nb, t_pipe *pi)
{
	ft_putstr_fd("21sh: ", 2);
	ft_putstr_fd(str, 2);
	if (!ft_strncmp(str, "parse", 5))
		ft_putchar_fd('\n', 2);
	else
	{
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(args[nb[0] + 1], 2);
	}
	pipes_free(args, nb[1], pi);
}

static void		pipes_prepare(char **args, t_env *e, long nb)
{
	t_pipe		pi;
	long		i[4];

	e->ret = 1;
	ft_memset(i, 0, sizeof(*i) * 4);
	if ((pi.table = ft_tabnew(nb + 1)) == NULL)
		return (pipes_error("Insufficient Memory.", args, i, &pi));
	if ((pi.cmd = (char ***)malloc(sizeof(**pi.cmd) * (nb + 2))) == NULL)
		return (pipes_error("Insufficient Memory.", args, i, &pi));
	if ((pi.fds = (int *)malloc(sizeof(*pi.fds) * (nb + 2))) == NULL)
		return (pipes_error("Insufficient Memory.", args, i, &pi));
	pi.cmd[i[2]++] = args;
	pi.fds[i[3]++] = STDOUT_FILENO;
	pi.pipe = 0;
	pi.redir = 0;
	while (args[i[0]])
	{
		if (*args[i[0]] == '|')
		{
			if (i[0] == 0 || args[i[0] - 1] == NULL || args[i[0] + 1] == NULL)
				return (pipes_error("parse error near `|'", args, i, &pi));
			pi.table[i[1]++] = args[i[0]];
			pi.cmd[i[2]++] = &args[i[0] + 1];
			pi.fds[i[3]++] = STDOUT_FILENO;
			args[i[0]] = NULL;
		}
		else if (*args[i[0]] == '>')
		{
			if (args[i[0] + 1] == NULL)
				return (pipes_error("parse error near `\\n'", args, i, &pi));
			if ((pi.fds[i[3]++] = open(args[i[0] + 1], O_RDWR | O_TRUNC | O_CREAT, 0644)) == -1)
				return (pipes_error(strerror(errno), args, i, &pi));
			pi.table[i[1]++] = args[i[0]];
			pi.cmd[i[2]++] = &args[i[0] + 1];
			args[i[0]] = NULL;
		}
		else if (*args[i[0]] == '<')
		{
			if (args[i[0] + 1] == NULL)
				return (pipes_error("parse error near `\\n'", args, i, &pi));
			if ((pi.fds[i[3]++] = open(args[i[0] + 1], O_RDONLY)) == -1)
				return (pipes_error(strerror(errno), args, i, &pi));
			pi.table[i[1]++] = args[i[0]];
			pi.cmd[i[2]++] = &args[i[0] + 1];
			args[i[0]] = NULL;
		}
		i[0]++;
	}
	pi.table[i[1]] = NULL;
	pi.cmd[i[2]] = NULL;
	pi.fds[i[3]] = STDOUT_FILENO;
	init_sigint(1);
	restore_term();
	rework_cmd(&pi);
	pipes_loop(pi, e, 0);
	init_sigint(0);
	redefine_term();
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
		if (*args[i] == '|' || *args[i] == '>' || *args[i] == '<')
			nb++;
		i++;
	}
	if (nb > 0)
		pipes_prepare(args, e, nb);
	else
		check_and_exec(args, e);
}
