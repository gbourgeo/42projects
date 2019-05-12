/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unalias.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 00:57:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/23 11:41:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_dprintf.h"
#include "command.h"
#include "builtin_unalias.h"
#include "builtins.h"

static int		unalias_usage(char *cmd)
{
	ft_dprintf(STDERR_FILENO, "%s: usage: %s [-a] name [name [...]]\n",
	cmd, cmd);
	return (2);
}

static int		unalias_error(char *cmd, char *alias, t_s_env *e)
{
	ft_dprintf(STDERR_FILENO, "%s: ", e->progname);
	if (e->filein)
		ft_dprintf(STDERR_FILENO, "line %ld: ", e->filein);
	ft_dprintf(STDERR_FILENO, "%s: %s : not found\n", cmd, alias);
	return (1);
}

static int		unalias_all(t_alias **alias_list)
{
	if (alias_list)
		if (*alias_list)
		{
			unalias_all(&(*alias_list)->next);
			free((*alias_list)->key);
			if ((*alias_list)->value)
				free((*alias_list)->value);
			free(*alias_list);
			*alias_list = NULLALIAS;
		}
	return (0);
}

static int		unalias_alias(char *alias, t_alias **alias_list)
{
	t_alias		*ptr;

	ptr = *alias_list;
	while (ptr)
	{
		if (!ft_strcmp(alias, ptr->key))
		{
			if (ptr->prev)
				ptr->prev->next = ptr->next;
			else
				*alias_list = ptr->next;
			if (ptr->next)
				ptr->next->prev = ptr->prev;
			free(ptr->key);
			if (ptr->value)
				free(ptr->value);
			free(ptr);
			return (0);
		}
		ptr = ptr->next;
	}
	return (1);
}

int				builtin_unalias(t_execute *exec, t_s_env *e)
{
	size_t		i;
	int			ret;

	i = 1;
	ret = 0;
	if (!exec->cmd[i])
		ret = unalias_usage(exec->cmd[0]);
	else if (!ft_strcmp(exec->cmd[i], "-a"))
		return (unalias_all(&e->alias_list));
	else
		while (exec->cmd[i])
		{
			if (unalias_alias(exec->cmd[i], &e->alias_list))
				ret |= unalias_error(exec->cmd[0], exec->cmd[i], e);
			i++;
		}
	return (ret);
}
