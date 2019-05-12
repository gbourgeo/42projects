/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_comment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 00:22:05 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/23 17:58:22 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token			*handle_comment(t_param *param, t_call *token)
{
	if (param->token->type == UNDEFINED)
	{
		param->token->type = TOKEN;
		param->token->id = COMMENT;
		while (param->line[param->i + 1]
		&& param->line[param->i + 1] != '\n')
			param->i++;
	}
	else if (param->token->type != TOKEN)
	{
		param->token = token[param->token->type].identifier(param);
		param->token = handle_comment(param, token);
	}
	return (param->token);
}
