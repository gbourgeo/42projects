/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_prepare.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 20:44:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/29 15:16:58 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"
#include "shell.h"
#include "command.h"
#include "command_error.h"
#include "operator_types.h"
#include "job_control.h"

static int		modify_env(char **cmd, t_s_env *e)
{
	char		**ptr;
	char		*equal;

	equal = ft_strchr(*cmd, '=');
	*equal = '\0';
	if ((ptr = sh_getnenvaddr(*cmd, e->public_env))
		|| (ptr = sh_getnenvaddr(*cmd, e->private_env)))
		free(*ptr);
	else if (!(ptr = sh_newenv(&e->private_env)))
		return (1);
	*equal = '=';
	*ptr = *cmd;
	*cmd = NULL;
	get_tree_env();
	return (0);
}

static int		modify_public_env(t_execute *exec, t_s_env *e)
{
	t_argument	*var;
	size_t		i;

	var = exec->variable;
	*e->ret = 0;
	while (var)
	{
		i = 0;
		while (var->cmd[i])
			if ((*e->ret = modify_env(&var->cmd[i], e)))
				break ;
			else
				i++;
		var = var->next;
	}
	free(exec);
	return (*e->ret);
}

int				command_prepare(t_execute *exec, t_s_env *e, int type)
{
	t_argument	*ptr;

	ptr = exec->variable;
	while (ptr && ptr->token && ptr->token->id == ASSIGNMENT_WORD)
		ptr = ptr->next;
	exec->command = ptr;
	if (exec->variable != exec->command && !exec->command)
		return (modify_public_env(exec, e));
	if (!(exec->cmd = command_group_command(exec->command)))
		return (command_error(e->progname, ERR_MALLOC, NULL, e));
	if (!e->forked)
		sh_setenv("_", exec->cmd[0], &e->public_env);
	if (!(exec->env = command_group_env(exec->variable, exec->command,
	(const char **)e->public_env)))
		return (command_error(e->progname, ERR_MALLOC, exec->cmd, e));
	exec->pv_env = e->private_env;
	if (!(create_process(e, exec, type)))
		return (command_error(e->progname, ERR_MALLOC, exec->cmd, e));
	return (0);
}
