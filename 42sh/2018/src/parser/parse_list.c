/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 20:39:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/24 17:01:19 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_errors.h"
#include "parser.h"

int				parse_list(t_token **token, t_p_param *param, t_s_env *e)
{
	t_command	*cmd;

	cmd = (t_command *)(*param->list)->aolist->cmd;
	if (!cmd->args)
		return (parse_error(ERR_UNEXPECTED_TOKEN, *token, e));
	if ((*token)->next && !new_tree(*token, param, &(*param->list)->next))
		return (parse_error(ERR_MALLOC_FAILED, NULLTOKEN, e));
	return (1);
}
