/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_newline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 20:16:48 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/25 15:29:06 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "token_error.h"
#include "operator_types.h"
#include "parser.h"
#include "command.h"

static void		get_hdoc(t_param *param, size_t start)
{
	size_t		i;
	t_token		*token;
	t_token		*eof;

	i = start;
	token = (t_token *)param->hdoc->token;
	eof = token->next;
	while (param->line[i])
	{
		param->e->filein++;
		while (param->line[i] && param->line[i] != '\n')
			i++;
		if (eof->len == i - param->i
		&& !ft_strncmp(eof->head, param->line + param->i, eof->len))
			break ;
		param->i = (param->line[i]) ? ++i : i;
	}
	if (!param->line[i]
	&& ft_strncmp(eof->head, param->line + param->i, eof->len))
		token_error(ERR_HEREDOC_EOF, param);
	hdoc_remove(&param->hdoc);
	token->hdocline = param->line + start;
	token->hdoclen = param->i - start;
	param->i = i;
}

static t_token	*exec_line(t_param *param)
{
	t_m_list	*tree;

	if (!(tree = parse((char **)param->line, &param->head, param->e)))
		return (NULLTOKEN);
	execute_list(tree, param->e);
	free_m_list(&tree);
	free_token(&param->head);
	if (!param->line[param->i])
		return (NULLTOKEN);
	if (!(param->token = new_token(param->line + param->i + 1, 0)))
		return (token_error(ERR_MALLOC, param));
	param->line = param->line + param->i + 1;
	param->i = 0;
	param->head = param->token;
	free_m_list(&tree);
	return (param->token);
}

t_token			*handle_newline(t_param *param, t_call *token)
{
	if (param->e->filein)
		++param->e->filein;
	if (param->token->type == UNDEFINED && !param->token->prev)
		return (param->token);
	if (param->token->type != UNDEFINED)
	{
		if (quote_type(param->token->quote) != NO_QUOTE)
			return (param->token);
		--param->e->filein;
		param->token = token[param->token->type].identifier(param);
		if (param->hdoc)
			get_hdoc(param, ++param->i);
		param->token = exec_line(param);
		++param->e->filein;
		param->i--;
		return (param->token);
	}
	if (param->token->prev->type != OPERATOR
	|| param->token->prev->id != NEWLINE_VALUE)
		param->token->type = OPERATOR;
	return (param->token);
}
