/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_prep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 14:45:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/10 14:58:10 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <fcntl.h>
#include <string.h>
#include <errno.h>

static int		init_t_pipe(char **args, long nb, long *i, t_pipe *pi)
{
	ft_memset(i, 0, sizeof(*i) * 4);
	if ((pi->table = ft_tabnew(nb + 1)) == NULL)
		return (pipes_error("Insufficient Memory.", args, i, pi));
	if ((pi->cmd = (char ***)malloc(sizeof(**pi->cmd) * (nb + 2))) == NULL)
		return (pipes_error("Insufficient Memory.", args, i, pi));
	if ((pi->fds = (int *)malloc(sizeof(*pi->fds) * (nb + 2))) == NULL)
		return (pipes_error("Insufficient Memory.", args, i, pi));
	pi->cmd[i[2]++] = args;
	pi->fds[i[3]++] = STDOUT_FILENO;
	pi->pipe = 0;
	pi->redir = 0;
	return (0);
}

static int		pipe_pipe(long *i, char **args, t_pipe *pi)
{
	if (i[0] == 0 || args[i[0] - 1] == NULL || args[i[0] + 1] == NULL)
		return (pipes_error("parse error near `|'", args, i, pi));
	pi->table[i[1]++] = args[i[0]];
	pi->cmd[i[2]++] = &args[i[0] + 1];
	pi->fds[i[3]++] = STDOUT_FILENO;
	args[i[0]] = NULL;
	return (0);
}

static int		pipe_left(long *i, char **args, t_pipe *pi)
{
	if (args[i[0] + 1] == NULL)
		return (pipes_error("parse error near `\\n'", args, i, pi));
	if ((pi->fds[i[3]++] = open(args[i[0] + 1], O_RDONLY)) == -1)
		return (pipes_error(strerror(errno), args, i, pi));
	pi->table[i[1]++] = args[i[0]];
	pi->cmd[i[2]++] = &args[i[0] + 1];
	args[i[0]] = NULL;
	return (0);
}

static int		pipe_right(long *i, char **args, t_pipe *pi)
{
	if (args[i[0] + 1] == NULL)
		return (pipes_error("parse error near `\\n'", args, i, pi));
	if ((pi->fds[i[3]++] = open(args[i[0] + 1], O_RDWR | O_TRUNC | O_CREAT, 0644)) == -1)
		return (pipes_error(strerror(errno), args, i, pi));
	pi->table[i[1]++] = args[i[0]];
	pi->cmd[i[2]++] = &args[i[0] + 1];
	args[i[0]] = NULL;
	return (0);
}

int				pipes_prepare(char **args, t_env *e, long nb)
{
	t_pipe		pi;
	long		i[4];

	if (init_t_pipe(args, nb, i, &pi))
		return (1);
	while (args[i[0]])
	{
		if ((*args[i[0]] == '|' && pipe_pipe(i, args, &pi)) ||
			(args[i[0]] && *args[i[0]] == '>' && pipe_right(i, args, &pi)) ||
			(args[i[0]] && *args[i[0]] == '<' && pipe_left(i, args, &pi)))
			return (1);
		i[0]++;
	}
	pi.table[i[1]] = NULL;
	pi.cmd[i[2]] = NULL;
	pi.fds[i[3]] = STDOUT_FILENO;
	init_sigint(1);
	restore_term();
	pipes_rework(&pi);
	pipes_loop(pi, e, 0);
	init_sigint(0);
	redefine_term();
	pipes_free(args, nb, &pi);
	return (e->ret);
}
