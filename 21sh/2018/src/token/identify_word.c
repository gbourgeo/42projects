/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 22:30:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/06 18:55:33 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin_alias.h"
#include "grammar_rules.h"
#include "reserved_words.h"
#include "operator_types.h"

static int		ionumber_type(t_token *token)
{
	size_t		i;

	i = 0;
	while (i < token->len && ft_isdigit(token->head[i]))
		i++;
	return ((i == token->len) ? IO_NUMBER : WORD);
}

static int		reserved_type(t_param *param)
{
	static t_ope	reserve[] = {
		TOKEN_BANG, TOKEN_BRACE_OPEN, TOKEN_BRACE_CLOSE, TOKEN_CASE, TOKEN_DO,
		TOKEN_DONE, TOKEN_ELIF, TOKEN_ELSE, TOKEN_ESAC, TOKEN_FI, TOKEN_FOR,
		TOKEN_IF, TOKEN_IN, TOKEN_THEN, TOKEN_UNTIL, TOKEN_WHILE,
	};
	size_t			i;
	size_t			len;

	i = 0;
	if (!param->token->prev
	|| (param->token->prev->type == OPERATOR && param->token->id < SEMI_VALUE))
		while (i < sizeof(reserve) / sizeof(reserve[0]))
		{
			if ((len = ft_strlen(reserve[i].name)) < param->token->len)
				len = param->token->len;
			if (!ft_strncmp(reserve[i].name, param->token->head, len))
				return (RESERVED_WORD);
			i++;
		}
	return (WORD);
}

static int		name_type(t_token *token)
{
	size_t		i;

	i = 0;
	if (ft_isdigit(token->head[0]))
		return (WORD);
	while (i < token->len)
		if (ft_isname(token->head[i++]))
			return (WORD);
	return (NAME);
}

t_token			*identify_word(t_param *param)
{
	if (!param->token->alias)
		param->token->len = param->line + param->i - param->token->head;
	else
	{
		param->token->len = ft_strlen(param->token->head);
		param->token->alen = param->line + param->i - param->token->alias;
	}
	if (ft_isquote(*param->token->head))
		param->token->id = WORD;
	else if (param->token->id == WORD
		&& (param->token->id = reserved_type(param)) == WORD)
	{
		if (param->line[param->i] == '<' || param->line[param->i] == '>')
			param->token->id = ionumber_type(param->token);
		else
			param->token->id = name_type(param->token);
		if (!(param->token = handle_alias(param, param->e)))
			return (param->token);
		if (quote_type(param->token->quote) != NO_QUOTE)
			return (token_error(ERR_INVALID_KEY, param));
	}
	if (!(param->token->next = new_token(param->line, param->i)))
		return (token_error(ERR_MALLOC, param));
	param->token->next->prev = param->token;
	return (param->token->next);
}
