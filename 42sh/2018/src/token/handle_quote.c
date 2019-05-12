/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 11:36:16 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/23 17:59:25 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token_error.h"
#include "token.h"

t_token			*handle_quote(t_param *param, t_call *token)
{
	static t_quote_h	quote[] = {
		{ '\\', backslash, BACKSLASH },
		{ '"', doublequote, DOUBLE_QUOTE },
		{ '\'', singlequote, SINGLE_QUOTE },
		{ '{', braceopen, BRACE },
		{ '}', braceclose, BRACE },
		{ '(', parentheseopen, PARENTHESE },
		{ ')', parentheseclose, PARENTHESE },
		{ '`', backquote, BACKQUOTE },
	};
	size_t				i;

	i = 0;
	if (param->token->type == UNDEFINED)
		param->token->type = TOKEN;
	else if (param->token->type == OPERATOR)
		param->token = token[OPERATOR].identifier(param);
	while (i < sizeof(quote) / sizeof(*quote))
	{
		if (param->line[param->i] == quote[i].value)
			return (quote[i].handler(param, quote[i].type));
		i++;
	}
	return (param->token);
}
