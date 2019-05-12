/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_alias.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 21:08:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/15 02:19:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"
#include "shell_env.h"
#include "operator_types.h"
#include "builtin_alias.h"

static int		is_token_a_command(t_token *token)
{
	return (token->type == OPERATOR && token->id < LESS_VALUE);
}

static void		alias_new_tokens(t_param *param, t_token *save)
{
	while (param->token->next)
		param->token = param->token->next;
	if (param->token->quote)
	{
		param->token->alen = param->line + param->i - save->head;
		param->token->alias = param->line + param->i;
	}
}

t_token			*handle_alias(t_param *param, t_s_env *e)
{
	t_alias		*alias;
	t_token		*save;

	if (param->token->prev && (!is_token_a_command(param->token->prev)
	|| !is_alias_valid_name(param->token->head, param->token->len)))
		return (param->token);
	alias = alias_get(param->token->head, param->token->len, e->alias_list);
	if (!alias)
		return (param->token);
	alias->in_use = 1;
	save = param->token;
	param->token = tokenise(&alias->value, e);
	alias->in_use = 0;
	if (save->prev)
		save->prev->next = param->token;
	else
		param->head = param->token;
	if (param->token)
		alias_new_tokens(param, save);
	free(save);
	return (param->token);
}
