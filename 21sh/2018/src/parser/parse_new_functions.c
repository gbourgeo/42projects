/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_new_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:24:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/10 19:13:17 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "operator_types.h"
#include "parser.h"

t_m_list		**new_m_list(t_token *token, t_m_list **list)
{
	if (!token || token->type == UNDEFINED)
		return (NULL);
	if ((*list = ft_memalloc(sizeof(**list))) == NULLLIST)
		return (NULL);
	return (list);
}

t_ao_list		**new_ao_list(t_token *token, t_ao_list **list)
{
	if ((*list = ft_memalloc(sizeof(**list))) == NULLAOLIST)
		return (NULL);
	if (token->type == OPERATOR
		&& (token->id == OR_IF_VALUE || token->id == AND_IF_VALUE))
		(*list)->type = token->id;
	return (list);
}

void			**new_command(void **cmd)
{
	if ((*cmd = ft_memalloc(sizeof(t_command))) == NULL)
		return (NULL);
	((t_command *)(*cmd))->type = IS_A_COMMAND;
	return (cmd);
}

int				new_tree(t_token *token, t_p_param *param, t_m_list **list)
{
	if (!(param->list = new_m_list(token, list)))
		return (0);
	if (!(param->aolist = new_ao_list(token, &(*list)->aolist)))
		return (0);
	if (!(param->cmd = new_command(&(*list)->aolist->cmd)))
		return (0);
	param->arg = &((t_command *)*param->cmd)->args;
	param->redir = &((t_command *)*param->cmd)->redir;
	return (1);
}
