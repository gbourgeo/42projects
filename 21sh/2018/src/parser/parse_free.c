/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 18:06:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/21 23:47:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "parser.h"

static void		free_args(t_argument **arg)
{
	size_t		i;

	if (!*arg)
		return ;
	free_args(&(*arg)->next);
	i = 0;
	if ((*arg)->cmd)
	{
		while ((*arg)->cmd[i])
		{
			free((*arg)->cmd[i]);
			(*arg)->cmd[i] = NULL;
			i++;
		}
		free((*arg)->cmd);
	}
	ft_memset(*arg, 0, sizeof(**arg));
	free(*arg);
	*arg = NULLARG;
}

static void		free_redir(t_redirection **redir)
{
	if (!*redir)
		return ;
	free_redir(&(*redir)->next);
	if ((*redir)->arg)
		free_args(&(*redir)->arg);
	if ((*redir)->fdarg != STDIN_FILENO && (*redir)->fdarg != STDOUT_FILENO
	&& (*redir)->fdarg != STDERR_FILENO && (*redir)->fdarg > 0)
		close((*redir)->fdarg);
	if ((*redir)->file)
	{
		unlink((*redir)->file);
		free((*redir)->file);
	}
	ft_memset(*redir, 0, sizeof(**redir));
	free(*redir);
	*redir = NULLREDIR;
}

static void		free_command(void **node)
{
	t_command	*cmd;
	t_pipeline	*pipe;

	cmd = (t_command *)*node;
	pipe = (t_pipeline *)*node;
	if (*node == NULL)
		return ;
	if (cmd->type == IS_A_COMMAND)
	{
		free_args(&cmd->args);
		free_redir(&cmd->redir);
		ft_memset(cmd, 0, sizeof(*cmd));
	}
	if (pipe->type == IS_A_PIPE)
	{
		free_command(&pipe->left);
		free_command(&pipe->right);
		ft_memset(pipe, 0, sizeof(*pipe));
	}
	free(*node);
	*node = NULL;
}

static void		free_ao_list(t_ao_list **list)
{
	if ((*list) == NULLAOLIST)
		return ;
	free_ao_list(&(*list)->next);
	free_command(&(*list)->cmd);
	ft_memset(*list, 0, sizeof(**list));
	free(*list);
	*list = NULL;
}

void			free_m_list(t_m_list **list)
{
	if (*list == NULLLIST)
		return ;
	free_m_list(&(*list)->next);
	if ((*list)->aolist)
		free_ao_list(&(*list)->aolist);
	ft_memset(*list, 0, sizeof(**list));
	free(*list);
	*list = NULLLIST;
}
