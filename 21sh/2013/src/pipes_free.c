/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/10 14:46:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/10 14:46:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			pipes_free(char **args, long nb, t_pipe *pi)
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
