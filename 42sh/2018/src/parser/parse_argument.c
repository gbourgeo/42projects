/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 20:44:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/15 03:23:37 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser_errors.h"
#include "parser.h"

int			parse_argument(t_token **token, t_p_param *param, t_s_env *e)
{
	if ((*token)->quote)
		return (parse_error(ERR_QUOTE, NULLTOKEN, e));
	if ((*param->arg = ft_memalloc(sizeof(**param->arg))) == NULLARG)
		return (parse_error(ERR_MALLOC_FAILED, NULLTOKEN, e));
	(*param->arg)->token = *token;
	param->arg = &(*param->arg)->next;
	return (1);
}
