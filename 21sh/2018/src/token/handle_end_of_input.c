/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_end_of_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 23:42:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/29 21:32:35 by gbourgeo         ###   ########.fr       */
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

static int		check_hdoc(t_hdoc *hdoc)
{
	return (hdoc && ((t_token *)hdoc->token)->next
	&& ((t_token *)hdoc->token)->next->type == TOKEN);
}

t_token			*handle_end_of_input(t_param *param, t_call *token)
{
	if (param->token->oldhd)
		param->token->oldlen = param->line + param->i - param->token->oldhd;
	else
		param->token->len = param->line + param->i - param->token->head;
	if (param->token->type != UNDEFINED)
	{
		if (param->e->checkquote && (quote_type(param->token->quote) != NO_QUOTE
			|| check_hdoc(param->hdoc)))
		{
			if (!param->e->filein)
			{
				param->token = quote_line(param);
				return (param->token);
			}
			else if (param->hdoc)
				token_error(ERR_HEREDOC_EOF, param);
			else
				param->token = token_error(ERR_MATCHING_EOF, param);
		}
		else
			param->token = token[param->token->type].identifier(param);
		param->i--;
	}
	clean_end_token(&param->token, &param->head);
	return (param->token);
}
