/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_get_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 09:26:39 by dbaffier          #+#    #+#             */
/*   Updated: 2019/04/29 19:00:38 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"

static const char	*get_head(t_m_list *list)
{
	t_command		*cmd;
	const char		*head;

	cmd = (t_command *)list->aolist->cmd;
	if (cmd->type == IS_A_PIPE)
	{
		if (!((t_command *)((t_pipeline *)cmd)->left)->args)
			return (NULL);
		if (!((t_command *)((t_pipeline *)cmd)->left)->args->token->oldhd
		|| !((t_command *)((t_pipeline *)cmd)->left)->args->token->oldhd[0])
			head = ((t_command *)((t_pipeline *)cmd)->left)->args->token->head;
		else
			head = ((t_command *)((t_pipeline *)cmd)->left)->args->token->oldhd;
	}
	else
	{
		if (!cmd->args || !cmd->args->token)
			return (NULL);
		if (!cmd->args->token->oldhd || !cmd->args->token->oldhd[0])
			head = cmd->args->token->head;
		else
			head = cmd->args->token->oldhd;
	}
	return (head);
}

static char			*check_head_tail(const char *head, const char *tail)
{
	if (tail > head)
		return (ft_strndup((char *)head, tail - head));
	return (ft_strndup((char *)head, head - tail));
}

char				*get_command(t_m_list *list)
{
	t_ao_list		*ao;
	t_command		*cmd;
	t_argument		*arg;
	const char		*tail;
	const char		*head;

	if (!list || !list->aolist || !list->aolist->cmd)
		return (NULL);
	if (!(head = get_head(list)))
		return (NULL);
	ao = list->aolist;
	while (ao->next)
		ao = ao->next;
	cmd = ao->cmd;
	while (cmd->type == IS_A_PIPE)
		cmd = ((t_pipeline *)cmd)->right;
	if (!(arg = cmd->args))
		return (NULL);
	while (arg->next)
		arg = arg->next;
	if (!arg->token->oldhd || !arg->token->oldhd[0])
		tail = arg->token->head + arg->token->len;
	else
		tail = arg->token->oldhd + arg->token->oldlen;
	return (check_head_tail(head, tail));
}
