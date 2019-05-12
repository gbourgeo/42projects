/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_minus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 05:48:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/23 17:58:49 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_error.h"
#include "token.h"

t_token				*handle_minus(t_param *param, t_call *token)
{
	if (param->token->type == UNDEFINED)
	{
		param->token->type = TOKEN;
		return (param->token);
	}
	else if (param->token->type == TOKEN)
		return (param->token);
	param->token = token[param->token->type].identifier(param);
	if (param->token->prev->head[param->token->prev->len - 1] != '&')
		return (param->token);
	if (!(param->token->next = new_token(param->line, param->i + 1)))
		return (token_error(ERR_MALLOC, param));
	param->token->next->prev = param->token;
	param->token->len++;
	return (param->token->next);
}
