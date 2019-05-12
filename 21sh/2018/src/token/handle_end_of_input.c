/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_end_of_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 23:42:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/15 03:57:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"
#include "token_error.h"

void			clean_end_token(t_token **token, t_token **head)
{
	if (!*token)
		return ;
	if ((*token)->type != UNDEFINED
	&& ((*token)->type != TOKEN || (*token)->id != COMMENT))
		return ;
	clean_end_token(&(*token)->prev, head);
	if ((*token)->prev)
		(*token)->prev->next = NULLTOKEN;
	if (*token == *head)
		*head = NULLTOKEN;
	ft_memset(*token, 0, sizeof(**token));
	free(*token);
	*token = NULLTOKEN;
}

t_token			*handle_end_of_input(t_param *param, t_call *token)
{
	param->token->len = param->line + param->i - param->token->head;
	if (param->token->type != UNDEFINED)
	{
		if (quote_type(param->token->quote) != NO_QUOTE)
		{
			if (!param->e->interactive)
				return ((param->token = quote_line(param)));
			else
				token_error(ERR_EOF, param);
		}
		param->token = token[param->token->type].identifier(param);
	}
	clean_end_token(&param->token, &param->head);
	return (NULLTOKEN);
}
