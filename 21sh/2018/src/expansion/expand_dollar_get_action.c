/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_get_action.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 06:50:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/20 20:50:24 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion_is.h"
#include "expansion_action.h"
#include "expansion_errors.h"
#include "expansion_dollar.h"

static int		action_percent(t_ret *parameter, t_exp *param)
{
	parameter->action = REMOVE_SMALLEST_SUFFIX_PATTERN;
	++param->i;
	if (param->buff[param->i] == '%')
	{
		parameter->action = REMOVE_LARGEST_SUFFIX_PATTERN;
		++param->i;
	}
	return (ERR_NONE);
}

static int		action_hash(t_ret *parameter, t_exp *param)
{
	parameter->action = REMOVE_SMALLEST_PREFIX_PATTERN;
	++param->i;
	if (param->buff[param->i] == '#')
	{
		parameter->action = REMOVE_LARGEST_PREFIX_PATTERN;
		++param->i;
	}
	return (ERR_NONE);
}

static int		action_values(t_ret *parameter, t_exp *param)
{
	if (param->buff[param->i] == '-')
		parameter->action |= ACT_NULL_SUBST;
	else if (param->buff[param->i] == '=')
		parameter->action |= ACT_NULL_ASSIGN;
	else if (param->buff[param->i] == '?')
		parameter->action |= ACT_NULL_ERROR;
	else if (param->buff[param->i] == '+')
		parameter->action |= ACT_NONNULL_SUBST;
	++param->i;
	return (ERR_NONE);
}

static int		action_colon(t_ret *parameter, t_exp *param)
{
	parameter->action = COLON_ACTION;
	++param->i;
	if (ft_strchr("-=?+", param->buff[param->i]))
		return (action_values(parameter, param));
	return (ERR_MODIFIER);
}

int				expand_dollar_get_action(t_ret *parameter, t_exp *param)
{
	static t_action	action[] = {
		{ ":", action_colon }, { "-=?+", action_values },
		{ "#", action_hash }, { "%", action_percent },
	};
	size_t			i;

	i = 0;
	parameter->action = NO_ACTION;
	if (!parameter->brace
		|| is_expand_null(parameter)
		|| param->buff[param->i] == '}')
		return (ERR_NONE);
	while (i < sizeof(action) / sizeof(action[0]))
	{
		if (ft_strchr(action[i].value, param->buff[param->i]))
			return (action[i].handler(parameter, param));
		i++;
	}
	return (ERR_SYNTAX);
}
