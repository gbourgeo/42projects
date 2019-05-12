/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 17:00:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/25 08:52:49 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "handler.h"
#include "parser_errors.h"
#include "parser.h"

static int		parse_not_handled_yet(t_token **tok, t_p_param *par, t_s_env *e)
{
	(void)par;
	return (parse_error(ERR_NOT_HANDLED_YET, *tok, e));
}

static int		parse_loop(t_token **token, t_p_param *param, t_s_env *e)
{
	static t_p_call		type_token[] = {
		H_ARGUMENT, H_ARGUMENT, H_ARGUMENT, H_IO_NUMBER, H_ERROR,
	};
	static t_p_call		type_operator[] = {
		{ NULL }, H_AO_LIST, H_PIPE, H_OPERATOR, H_ERROR, H_AO_LIST,
		H_ASYNC, H_LIST, H_LIST, H_ERROR, H_OPERATOR, H_OPERATOR, H_OPERATOR,
		H_OPERATOR, H_OPERATOR, H_OPERATOR, H_OPERATOR, H_OPERATOR,
		H_OPERATOR, H_OPERATOR, H_OPERATOR, H_OPERATOR,
	};
	static t_t_p_call	call[] = {
		{ type_token }, { type_operator },
	};
	t_token				*ptr;

	ptr = *token;
	while (ptr)
	{
		if (ptr->type != UNDEFINED
		&& call[ptr->type].type[ptr->id].handler
		&& !call[ptr->type].type[ptr->id].handler(&ptr, param, e))
			return (0);
		if (ptr)
			ptr = ptr->next;
	}
	return (1);
}

t_m_list		*parse(char **line, t_token **token, t_s_env *e)
{
	t_m_list	*list;
	t_p_param	param;

	list = NULLLIST;
	ft_memset(&param, 0, sizeof(param));
	param.line = line;
	param.token = token;
	if (!new_tree(*token, &param, &list))
		parse_error(ERR_MALLOC_FAILED, NULLTOKEN, e);
	else if (!parse_loop(token, &param, e))
		free_m_list(&list);
	debug_parser(list);
	return (list);
}
