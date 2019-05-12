/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_squote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 00:17:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/29 13:56:27 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_loop.h"
#include "expansion_errors.h"

int				expand_squote(t_exp *param, t_ret *ret)
{
	int			error;
	size_t		i;

	error = ERR_NONE;
	i = param->i;
	if (quote_type(param->quote) != DOUBLE_QUOTE)
	{
		if (!quote_add(&param->quote, SINGLE_QUOTE, 0))
			return (ERR_MALLOC);
		while (param->i - i < param->buff_len
		&& (error = param_addchar(param->buff[param->i++], ret)) == ERR_NONE)
			if (param->buff[param->i] == '\'')
				break ;
		if (param->buff[param->i] == '\'')
			quote_remove(&param->quote, SINGLE_QUOTE);
	}
	return ((error == ERR_NONE && param->i - i < param->buff_len)
		? param_addchar(param->buff[param->i], ret) : error);
}
