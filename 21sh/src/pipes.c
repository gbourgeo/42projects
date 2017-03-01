/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 00:25:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/01 14:07:31 by gbourgeo         ###   ########.fr       */
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
	while (count < nb)
	{
		if (pi->fds[count] > STDOUT_FILENO)
			close(pi->fds[count]);
		while (args[i])
			i++;
		args[i] = pi->table[count];
		count++;
	}
	if (pi->fds[count] > STDIN_FILENO)
		close(pi->fds[count]);
	if (pi->table)
		free(pi->table);
	if (pi->cmd)
		free(pi->cmd);
	if (pi->fds)
		free(pi->fds);
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
	long		i[4];

	if ((pi.table = ft_tabnew(nb + 1)) == NULL)
		return (pipes_error("Insufficient Memory.", args, 0, &pi));
	if ((pi.cmd = (char ***)malloc(sizeof(**pi.cmd) * (nb + 2))) == NULL)
		return (pipes_error("Insufficient Memory.", args, 0, &pi));
	if ((pi.fds = (int *)malloc(sizeof(*pi.fds) * (nb + 1))) == NULL)
		return (pipes_error("Insufficient Memory.", args, 0, &pi));
	ft_memset(i, 0, sizeof(*i) * 4);
	pi.cmd[i[2]++] = args;
	pi.fds[i[3]++] = STDOUT_FILENO;
	while (args[i[0]])
	{
		if (*args[i[0]] == '|')
		{
			if (i[0] == 0 || args[i[0] - 1] == NULL || args[i[0] + 1] == NULL)
				return (pipes_error("parse error near `|'", args, i[1], &pi));
			pi.fds[i[3]++] = 1;
			pi.table[i[1]++] = args[i[0]];
			args[i[0]] = NULL;
			pi.cmd[i[2]++] = &args[i[0] + 1];
		}
		else if (*args[i[0]] == '>')
		{
			if (args[i[0] + 1] == NULL)
				return (pipes_error("parse error near `\\n'", args, i[1], &pi));
			if ((pi.fds[i[3]++] = open(args[i[0] + 1], O_WRONLY | O_TRUNC | O_CREAT, 0644)) == -1)
				return (pipes_error(strerror(errno), args, i[1], &pi));
			pi.table[i[1]++] = args[i[0]];
			args[i[0]] = NULL;
			pi.cmd[i[2]++] = &args[i[0] + 1];
		}
		else if (*args[i[0]] == '<')
		{
			if (args[i[0] + 1] == NULL)
				return (pipes_error("parse error near `\\n'", args, i[1], &pi));
			if ((pi.fds[i[3]++] = open(args[i[0] + 1], O_RDONLY)) == -1)
				return (pipes_error(strerror(errno), args, i[1], &pi));
			pi.table[i[1]++] = args[i[0]];
			args[i[0]] = NULL;
			pi.cmd[i[2]++] = &args[i[0] + 1];
		}
		i[0]++;
	}
	pi.cmd[i[2]] = NULL;
	pipes_loop(pi, e);
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
