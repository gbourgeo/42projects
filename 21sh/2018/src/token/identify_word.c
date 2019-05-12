/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 22:30:29 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/27 18:47:41 by gbourgeo         ###   ########.fr       */
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

static int		identify_alias(t_param *param)
{
	t_token		*token;
	t_token		*prev;

	token = param->token;
	prev = param->token->prev;
	if ((!prev
	|| (prev->type == OPERATOR && prev->id < LESS_VALUE)
	|| (prev->type == TOKEN && prev->alias
		&& ft_isspace(prev->alias->value[ft_strlen(prev->alias->value) - 1])
		&& quote_type(prev->quote) == NO_QUOTE))
	&& is_alias_valid_name(token->head, token->len)
	&& (param->token = handle_alias(param, param->e))
	&& quote_type(param->token->quote) != NO_QUOTE)
		return (1);
	return (0);
}

t_token			*identify_word(t_param *param)
{
	if (!param->token->oldhd)
		param->token->len = param->line + param->i - param->token->head;
	else
		param->token->oldlen = param->line + param->i - param->token->oldhd;
	if (ft_isquote(*param->token->head))
		param->token->id = WORD;
	else if (param->token->id == WORD
		&& (param->token->id = reserved_type(param)) == WORD)
	{
		if (param->line[param->i] == '<' || param->line[param->i] == '>')
			param->token->id = ionumber_type(param->token);
		else
			param->token->id = name_type(param->token);
		if (identify_alias(param) || !param->token)
			return (param->token);
	}
	if (!(param->token->next = new_token(param->line, param->i)))
		return (token_error(ERR_MALLOC, param));
	param->token->next->prev = param->token;
	return (param->token->next);
}
