/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dquote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 02:08:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/14 23:23:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_loop.h"
#include "expansion_errors.h"

int				expand_dquote(t_exp *param, t_ret *ret)
{
	if (quote_type(param->quote) == DOUBLE_QUOTE)
		quote_remove(&param->quote, DOUBLE_QUOTE);
	else if (!quote_add(&param->quote, DOUBLE_QUOTE, 0))
		return (ERR_MALLOC);
	return (param_addchar(param->buff[param->i], ret));
}
