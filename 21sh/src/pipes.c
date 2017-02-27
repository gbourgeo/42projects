/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 00:25:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/27 07:36:15 by gbourgeo         ###   ########.fr       */
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
		if (*args[i[0]] == '|')
		{
			if (i[0] == 0 || args[i[0] - 1] == NULL || args[i[0] + 1] == NULL ||
				ft_strlen(args[i[0]]) != 1)
				return (pipes_error("parse error near `|'", args, i[1], &pi));
			pi.table[i[1]++] = args[i[0]];
			args[i[0]] = NULL;
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
		if (*args[i] == '|')
			nb++;
		i++;
	}
	if (nb > 0)
		pipes_prepare(args, e, nb);
	else
		check_and_exec(args, e);
}
