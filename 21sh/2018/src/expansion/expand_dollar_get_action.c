/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_get_action.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 06:50:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/04/29 20:48:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "expansion_is.h"
#include "expansion_action.h"
#include "expansion_errors.h"
#include "expansion_dollar.h"

static int		action_percent(t_exp *param, t_ret *ret, int value)
{
	(void)param;
	++ret->i;
	ret->action = REMOVE_SMALLEST_SUFFIX_PATTERN;
	value = ret->head[ret->brace + ret->hash + ret->i];
	if (value == '%')
	{
		ret->action = REMOVE_LARGEST_SUFFIX_PATTERN;
		++ret->i;
	}
	return (ERR_NONE);
}

static int		action_hash(t_exp *param, t_ret *ret, int value)
{
	(void)param;
	++ret->i;
	ret->action = REMOVE_SMALLEST_PREFIX_PATTERN;
	value = ret->head[ret->brace + ret->hash + ret->i];
	if (value == '#')
	{
		ret->action = REMOVE_LARGEST_PREFIX_PATTERN;
		++ret->i;
	}
	return (ERR_NONE);
}

static int		action_values(t_exp *param, t_ret *ret, int value)
{
	(void)param;
	if (value == '-')
		ret->action |= ACT_NULL_SUBST;
	else if (value == '=')
		ret->action |= ACT_NULL_ASSIGN;
	else if (value == '?')
		ret->action |= ACT_NULL_ERROR;
	else if (value == '+')
		ret->action |= ACT_NONNULL_SUBST;
	ret->i++;
	return (ERR_NONE);
}

static int		action_colon(t_exp *param, t_ret *ret, int value)
{
	ret->action = COLON_ACTION;
	ret->i++;
	value = ret->head[ret->i];
	if (ft_strchr("-=?+", value))
		return (action_values(param, ret, value));
	return (expand_arithmetic(param, ret));
}

int				expand_dollar_get_action(t_ret *ret, t_exp *param)
{
	static t_action	action[] = {
		{ ":", action_colon }, { "-=?+", action_values },
		{ "#", action_hash }, { "%", action_percent },
	};
	size_t			i;
	int				value;

	i = 0;
	value = ret->head[ret->i];
	if (!ret->brace || is_expand_null(ret) || value == '}')
		return (ERR_NONE);
	while (i < sizeof(action) / sizeof(action[0]))
	{
		if (ft_strchr(action[i].value, value))
		{
			if (ret->hash
			|| (!is_valid_name(ret->word[ret->brace + 1])
				&& !is_special(ret->word[ret->brace + 1])))
				return (ERR_SYNTAX);
			return (action[i].handler(param, ret, value));
		}
		i++;
	}
	return (ERR_NONE);
}
