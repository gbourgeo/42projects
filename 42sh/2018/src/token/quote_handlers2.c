/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handlers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/16 18:10:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/23 18:01:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "token_error.h"

t_token			*parentheseopen(t_param *param, int type)
{
	if (quote_type(param->token->quote) == SINGLE_QUOTE)
		return (param->token);
	if (param->i && *(param->line + param->i - 1) == '$')
		type = D_PARENTHESE;
	if (!quote_add(&param->token->quote, type, param->e->filein))
		return (token_error(ERR_MALLOC, param));
	return (param->token);
}

t_token			*parentheseclose(t_param *param, int type)
{
	int			qtype;

	qtype = quote_type(param->token->quote);
	if (!param->token->quote)
		return (param->token);
	if (qtype == type || qtype == D_PARENTHESE)
		quote_remove(&param->token->quote, qtype);
	return (param->token);
}

t_token			*backquote(t_param *param, int type)
{
	int			qtype;

	qtype = quote_type(param->token->quote);
	if (qtype == SINGLE_QUOTE)
		return (param->token);
	if (qtype == BACKQUOTE)
		quote_remove(&param->token->quote, type);
	else if (!quote_add(&param->token->quote, type, param->e->filein))
		return (NULLTOKEN);
	return (param->token);
}
