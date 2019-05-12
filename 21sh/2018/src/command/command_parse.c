/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 01:23:07 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/28 18:49:10 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "main_tools.h"
#include "shell.h"
#include "command.h"
#include "job_control.h"
#include "command_error.h"
#include "operator_types.h"

static int		command_piped(void *cmd, t_s_env *e, int type)
{
	command_parse(((t_pipeline *)cmd)->left, e, type | PIPED);
	if (*(int *)((t_pipeline *)cmd)->right == IS_A_PIPE)
	{
		if (command_piped(((t_pipeline *)cmd)->right, e, PIPED))
			return (1);
	}
	else
		command_parse(((t_pipeline *)cmd)->right, e, END_OF_PIPE);
	return (0);
}

int				command_parse(void *cmd, t_s_env *e, int type)
{
	int			ret;
	t_execute	*exec;

	exec = NULL;
	ret = 0;
	if (*(int *)cmd == IS_A_PIPE)
		ret = command_piped(cmd, e, type);
	else
	{
		if (((t_command *)cmd)->args)
		{
			if (!(exec = ft_memalloc(sizeof(t_execute))))
				return (0);
			exec->async = ((t_command *)cmd)->async;
			exec->variable = ((t_command *)cmd)->args;
			exec->redirection = ((t_command *)cmd)->redir;
			ret = command_prepare(exec, e, type);
		}
	}
	return (ret);
}
