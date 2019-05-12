/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_io_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 20:44:12 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/12 18:41:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser_errors.h"
#include "parser.h"

int			parse_io_number(t_token **token, t_p_param *param, t_s_env *e)
{
	if ((*param->redir = ft_memalloc(sizeof(t_redirection))) == NULLREDIR)
		return (parse_error(ERR_MALLOC_FAILED, NULLTOKEN, e));
	(*param->redir)->ionumber = *token;
	return (1);
}
