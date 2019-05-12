/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 02:19:16 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/16 17:46:34 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "command.h"
#include "operator_types.h"
#include "expansion.h"
#include "redirection.h"

static int	prepare_redirect(t_redirection *cmd, t_s_env *e)
{
	if (!cmd)
		return (0);
	if (expand_argument(cmd->arg, e, 0))
		return (1);
	quote_removal(cmd->arg);
	if (redirection(&cmd, e))
		return (1);
	return (prepare_redirect(cmd->next, e));
}

static int	prepare_command(void *cmd, t_s_env *e)
{
	if (!cmd)
		return (0);
	if (*(int *)cmd == IS_A_PIPE)
		return (prepare_command(((t_pipeline *)cmd)->left, e)
		|| prepare_command(((t_pipeline *)cmd)->right, e));
	else if (expand_argument(((t_command *)cmd)->args, e, 1)
	|| prepare_redirect(((t_command *)cmd)->redir, e))
		return (1);
	quote_removal(((t_command *)cmd)->args);
	return (0);
}

static int	execute_ao_list(t_ao_list *aolist, t_s_env *e)
{
	if (!aolist)
		return (0);
	if (!aolist->type
	|| (aolist->type == OR_IF_VALUE && *e->ret)
	|| (aolist->type == AND_IF_VALUE && !*e->ret))
		if (!prepare_command(aolist->cmd, e))
			command_parse(aolist->cmd, e);
	return (execute_ao_list(aolist->next, e));
}

int			execute_list(t_m_list *list, t_s_env *e)
{
	pid_t	pid;

	pid = 0;
	if (!list)
		return (0);
	if (list->async)
	{
		if ((pid = fork()) < 0)
			return (1);
		if (pid == 0)
			exit(execute_ao_list(list->aolist, e));
	}
	else if (execute_ao_list(list->aolist, e))
		return (1);
	return (execute_list(list->next, e));
}
