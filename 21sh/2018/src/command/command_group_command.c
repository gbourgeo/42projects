/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_group_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 19:29:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/25 08:44:42 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "command.h"

static char		**alloc_command(t_argument *cmd)
{
	char		**ret;
	size_t		size;
	size_t		i;

	size = 0;
	while (cmd)
	{
		i = 0;
		if (cmd->cmd)
			while (cmd->cmd[i])
				i++;
		size += i;
		cmd = cmd->next;
	}
	return (ft_memalloc(sizeof(*ret) * (size + 1)));
}

char			**command_group_command(t_argument *cmd)
{
	char		**ret;
	size_t		i;
	size_t		j;

	if (!(ret = alloc_command(cmd)))
		return (NULL);
	i = 0;
	while (cmd)
	{
		j = 0;
		if (cmd->cmd)
			while (cmd->cmd[j])
				ret[i++] = cmd->cmd[j++];
		cmd = cmd->next;
	}
	return (ret);
}
