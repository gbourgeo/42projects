/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/05 10:59:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/30 00:31:44 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void		ft_exec_pipes(t_args *list, t_env *e)
{
	if ((list->type == DOUBLE_AND && e->status == 0)
		|| (list->type == DOUBLE_OR && e->status != 0)
		|| (list->type == 0))
		ft_pipex_or_exec(list, e);
}

static void		ft_exec(t_args *list, t_env *e)
{
	if ((list->type == DOUBLE_AND && e->status == 0)
		|| (list->type == DOUBLE_OR && e->status != 0)
		|| (list->type == 0))
		e->status = check_and_exec(list->args, e);
}

static void		ft_run_parser(t_args *list, t_env *e)
{
	pid_t		pid;

	while (list != NULL)
	{
		if (list->args && *list->args && list->pipe)
		{
			pid = fork();
			if (pid == 0)
			{
				ft_exec_pipes(list, e);
				exit(e->status);
			}
			else if (pid > 0)
				waitpid(pid, &e->status, 0);
			else
				ft_putendl("42sh: Fork error...");
		}
		else if (list->args && *list->args)
			ft_exec(list, e);
		list = list->next;
	}
}

static t_args	*ft_analyse(char **args, int type, t_env *e)
{
	int			i;
	t_args		*list;

	i = 0;
	if (!args || !*args || (list = ft_argsnew(args, type)) == NULL)
		return (NULL);
	while (args[i] && (ft_strcmp(args[i], ";") && ft_strcmp(args[i], "||")
			&& ft_strcmp(args[i], "&&")))
	{
		if (ft_strcharset(args[i], "<>|") && ft_strcmp(args[i], "||"))
			list->pipe++;
		i++;
	}
	if (!ft_strcmp(args[i], "||"))
		list->next = ft_analyse(&args[i + 1], DOUBLE_OR, e);
	else if (!ft_strcmp(args[i], "&&"))
		list->next = ft_analyse(&args[i + 1], DOUBLE_AND, e);
	else if (!ft_strcmp(args[i], ";"))
		list->next = ft_analyse(&args[i + 1], 0, e);
	free(list->args[i]);
	list->args[i] = NULL;
	return (list);
}

void			ft_parser(t_env *e)
{
	char		**args;
	char		*cmd;
	t_args		*list;

	list = NULL;
	args = NULL;
	if (!(cmd = ft_lexical_analysis(e->history->command)))
		return ;
	if (!(args = ft_split_whitespaces(cmd)))
		return ;
	if (!ft_syntax_analysis(args))
	{
		if ((list = ft_analyse(args, 0, e)))
		{
			ft_run_parser(list, e);
			ft_free_list(&list);
		}
	}
	ft_free(&args);
	free(cmd);
}
