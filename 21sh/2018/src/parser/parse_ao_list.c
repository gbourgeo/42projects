/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ao_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 20:43:39 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/12 18:40:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "operator_types.h"
#include "parser_errors.h"
#include "parser.h"

static int	check_token_next(t_token *token)
{
	if (token == NULLTOKEN)
		return (0);
	if (token->type == TOKEN)
		return (1);
	if (token->id < LESS_VALUE)
		return (0);
	return (1);
}

int			parse_ao_list(t_token **token, t_p_param *param, t_s_env *e)
{
	if (((t_command *)*param->cmd)->args == NULLARG
		&& ((t_command *)*param->cmd)->redir == NULLREDIR)
		return (parse_error(ERR_UNEXPECTED_TOKEN, *token, e));
	if (!check_token_next((*token)->next))
		return (parse_error(ERR_UNEXPECTED_TOKEN, (*token)->next, e));
	if (!(param->aolist = new_ao_list(*token, &(*param->aolist)->next)))
		return (parse_error(ERR_MALLOC_FAILED, NULLTOKEN, e));
	if (!(param->cmd = new_command(&(*param->aolist)->cmd)))
		return (parse_error(ERR_MALLOC_FAILED, NULLTOKEN, e));
	param->arg = &((t_command *)*param->cmd)->args;
	param->redir = &((t_command *)*param->cmd)->redir;
	return (1);
}
