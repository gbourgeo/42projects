/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_modify.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 19:16:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/01/27 11:26:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "command.h"
#include "shell_lib.h"
#include "parser.h"

char			**modify_environ(t_argument *var, t_execute *exec)
{
	char		**ptr;
	char		*equal;
	size_t		i;

	while (var != exec->command)
	{
		i = 0;
		while (var->cmd[i])
		{
			equal = ft_strchr(var->cmd[i], '=');
			*equal = '\0';
			if ((ptr = sh_getnenvaddr(var->cmd[i], exec->env)))
				free(*ptr);
			else if (!(ptr = sh_newenv(&exec->env)))
				return (NULL);
			*equal = '=';
			*ptr = var->cmd[i];
			var->cmd[i] = NULL;
			i++;
		}
		var = var->next;
	}
	return (exec->env);
}
