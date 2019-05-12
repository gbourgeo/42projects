/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 21:54:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/11 16:06:50 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

t_token			*handle_word(t_param *param, t_call *token)
{
	if (param->token->type == UNDEFINED)
		param->token->type = TOKEN;
	else if (param->token->type != TOKEN)
		param->token = token[param->token->type].identifier(param);
	return (param->token);
}
