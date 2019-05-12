/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 15:24:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/29 15:18:20 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "command.h"

void		command_free(t_execute *exec, char *name)
{
	size_t	i;

	i = 0;
	if (exec->env)
	{
		while (exec->env[i])
			free(exec->env[i++]);
		free(exec->env);
	}
	exec->env = NULL;
	if (exec->cmd)
		free(exec->cmd);
	exec->cmd = NULL;
	if (name)
		free(name);
	if (exec)
		free(exec);
}
