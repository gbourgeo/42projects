/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_operator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 00:38:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/23 17:59:33 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"
#include "token_error.h"
#include "operator_types.h"

static size_t	max(size_t a, size_t b)
{
	return ((a > b) ? a : b);
}

size_t			check_operator(t_token *token, size_t len)
{
	static t_ope	ope[] = {
		OP_OR_IF, OP_PIPE, OP_PIPE_AND, OP_NOT, OP_AND_IF, OP_BACKGRND, OP_SEMI,
		OP_NEWLINE, OP_DSEMI, OP_LESS, OP_LESSAND, OP_LESS_GREAT, OP_GREAT,
		OP_GREAT_PIPE, OP_AND_GREAT, OP_GREAT_AND, OP_DGREAT, OP_AND_DGREAT,
		OP_DLESS,
	};
	size_t			i;
	size_t			size;

	i = 0;
	while (i < sizeof(ope) / sizeof(ope[0]))
	{
		size = max(ft_strlen(ope[i].name), len);
		if (!ft_strncmp(ope[i].name, token->head, size))
			return (ope[i].value);
		i++;
	}
	return (0);
}

t_token			*identify_operator(t_param *param)
{
	param->token->len = param->line + param->i - param->token->head;
	param->token->id = check_operator(param->token, param->token->len);
	if (!(param->token->next = new_token(param->line, param->i)))
		return (token_error(ERR_MALLOC, param));
	param->token->next->prev = param->token;
	if (param->token->id == DLESS_VALUE)
		if (!hdoc_add(&param->hdoc, param->token, param->e->filein))
			return (token_error(ERR_MALLOC, param));
	return (param->token->next);
}
