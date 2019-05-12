/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_rework.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 14:49:45 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/10 14:50:38 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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

void			pipes_rework(t_pipe *pi)
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
