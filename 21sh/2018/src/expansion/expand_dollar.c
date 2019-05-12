/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 00:56:12 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/25 09:07:44 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion_dollar.h"
#include "expansion_errors.h"
#include "expansion_loop.h"

static int		check_expression(t_exp *param)
{
	size_t	j;
	size_t	depth;

	j = param->i + 2;
	depth = 1;
	while (j < param->buff_len && depth)
	{
		if (param->buff[j] == '(')
			++depth;
		else if (param->buff[j] == ')')
			--depth;
		++j;
	}
	return (param->buff[j - 2] == ')');
}

int				expand_dollar(t_exp *param, t_ret *ret)
{
	size_t		i;

	i = param->i + 1;
	if (param->buff[i] == '(')
	{
		if (param->buff[i + 1] == '(' && check_expression(param))
			return (expand_arithmetic(param, ret));
		return (expand_subshell(param, ret));
	}
	else if (param->buff[i] == '[')
		return (expand_arithmetic(param, ret));
	else if (param->buff[i] == '\'' || param->buff[i] == '"')
		return (expand_dollar_quote(param, ret));
	return (expand_dollar_parameter(param, ret));
}
