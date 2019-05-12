/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 20:42:12 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/23 17:09:35 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "operator_types.h"
#include "parser_errors.h"
#include "parser.h"

int			parse_operator(t_token **token, t_p_param *param, t_s_env *e)
{
	if (*param->redir == NULLREDIR)
		if (!(*param->redir = ft_memalloc(sizeof(**param->redir))))
			return (parse_error(ERR_MALLOC_FAILED, NULLTOKEN, e));
	(*param->redir)->token = *token;
	if ((*token)->next == NULL
	|| ((*token)->id == DLESS_VALUE && (*token)->next->type == OPERATOR))
		return (parse_error(ERR_UNEXPECTED_TOKEN, (*token)->next, e));
	if (!((*param->redir)->arg = ft_memalloc(sizeof(*(*param->redir)->arg))))
		return (parse_error(ERR_MALLOC_FAILED, NULLTOKEN, e));
	*token = (*token)->next;
	(*param->redir)->arg->token = *token;
	if ((*token)->type != TOKEN
		|| ((*token)->id != WORD && (*token)->id != NAME))
		return (parse_error(ERR_UNEXPECTED_TOKEN, *token, e));
	(*token)->id = 0;
	param->redir = &(*param->redir)->next;
	return (1);
}
