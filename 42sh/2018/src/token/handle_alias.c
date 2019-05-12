/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_alias.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 21:08:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/29 21:16:12 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"
#include "shell_env.h"
#include "operator_types.h"
#include "builtin_alias.h"

static void		alias_new_tokens(t_param *param, t_token *save)
{
	while (param->token->next)
	{
		param->token->oldhd = "";
		param->token->oldlen = 0;
		param->token->alias = save->alias;
		param->token = param->token->next;
	}
	param->token->oldhd = param->line + param->i;
	param->token->oldlen = 0;
	param->token->alias = save->alias;
	if (param->token->quote)
	{
		param->token->oldhd = param->line + param->i;
		param->token->oldlen = param->line + param->i - save->head;
	}
}

t_token			*handle_alias(t_param *param, t_s_env *e)
{
	t_alias		*alias;
	t_token		*save;

	alias = alias_get(param->token->head, param->token->len, e->alias_list);
	if (!alias)
		return (param->token);
	if (!param->token->alias)
		param->token->alias = alias;
	save = param->token;
	alias->in_use = 1;
	e->checkquote = 0;
	param->token = tokenise(&alias->value, e);
	e->checkquote = 1;
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
