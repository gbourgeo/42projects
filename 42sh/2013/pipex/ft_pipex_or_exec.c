/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_or_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/20 22:31:02 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/30 00:54:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static t_args	*ft_parse_pipes(char **args, int type)
{
	t_args	*pipes;
	int		i;

	i = 0;
	if ((pipes = ft_argsnew(args, type)) == NULL)
		return (NULL);
	while (args[i] && !ft_strequ(args[i], "<") && !ft_strequ(args[i], ">")
			&& !ft_strequ(args[i], "|") && !ft_strequ(args[i], ">>"))
		i++;
	if (ft_strequ(args[i], "<"))
		pipes->next = ft_parse_pipes(&args[i + 1], PIPE_LEFT);
	else if (ft_strequ(args[i], ">"))
		pipes->next = ft_parse_pipes(&args[i + 1], PIPE_RIGHT);
	else if (ft_strequ(args[i], "|"))
		pipes->next = ft_parse_pipes(&args[i + 1], PIPE_PIPE);
	else if (ft_strequ(args[i], ">>"))
		pipes->next = ft_parse_pipes(&args[i + 1], PIPE_RIGHT_2);
	free(pipes->args[i]);
	pipes->args[i] = NULL;
	return (pipes);
}

void			ft_pipex_or_exec(t_args *list, t_env *e)
{
	t_args		*pipes;
	t_args		*head;

	if ((pipes = ft_parse_pipes(list->args, 0)) == NULL)
		return ;
	head = pipes;
	while (pipes->next)
	{
		if (pipes->next->type == PIPE_PIPE)
			ft_pipe_pipe(pipes, e);
		else if (pipes->next->type == PIPE_LEFT)
			ft_pipe_left(pipes, e);
		else if (pipes->next->type == PIPE_RIGHT)
			ft_pipe_right(pipes, e);
		else if (pipes->next->type == PIPE_RIGHT_2)
			ft_pipe_right_2(pipes, e);
		pipes = pipes->next;
	}
	pipes = NULL;
	ft_free_list(&head);
}
