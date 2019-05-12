/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 20:43:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/12 18:42:45 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "operator_types.h"
#include "parser_errors.h"
#include "parser.h"

static int		check_token_next(t_token *token)
{
	if (token == NULLTOKEN)
		return (0);
	if (token->type == TOKEN)
		return (1);
	if (token->id < LESS_VALUE)
		return (0);
	return (1);
}

int				parse_pipe(t_token **token, t_p_param *param, t_s_env *e)
{
	t_pipeline			*ptr;

	ptr = (t_pipeline *)(*param->cmd);
	if (ptr == NULL || ptr->left == NULL || !check_token_next((*token)->next))
		return (parse_error(ERR_UNEXPECTED_TOKEN, *token, e));
	if ((*param->cmd = ft_memalloc(sizeof(*ptr))) == NULL)
		return (parse_error(ERR_MALLOC_FAILED, NULLTOKEN, e));
	((t_pipeline *)(*param->cmd))->type = IS_A_PIPE;
	((t_pipeline *)(*param->cmd))->left = ptr;
	if (!(param->cmd = new_command(&((t_pipeline *)(*param->cmd))->right)))
		return (parse_error(ERR_MALLOC_FAILED, NULLTOKEN, e));
	param->arg = &((t_command *)*param->cmd)->args;
	param->redir = &((t_command *)*param->cmd)->redir;
	return (1);
}
