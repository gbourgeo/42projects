/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_do_expansion.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 08:56:20 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/20 20:50:12 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion_dollar.h"
#include "expansion_action.h"

int				expand_dollar_do_expansion(t_ret *parameter)
{
	if (parameter->action == NO_ACTION)
		return (0);
	if (parameter->action & REMOVE_SMALLEST_SUFFIX_PATTERN
		|| parameter->action & REMOVE_LARGEST_SUFFIX_PATTERN
		|| parameter->action & REMOVE_SMALLEST_PREFIX_PATTERN
		|| parameter->action & REMOVE_LARGEST_PREFIX_PATTERN)
		return (1);
	else if (parameter->action & ACT_NULL_SUBST
		|| parameter->action & ACT_NULL_ASSIGN
		|| parameter->action & ACT_NULL_ERROR)
	{
		if (!parameter->substitute
			|| (!*parameter->substitute && parameter->action & COLON_ACTION))
			return (1);
	}
	else if (parameter->action & ACT_NONNULL_SUBST)
		if (parameter->substitute
			&& (*parameter->substitute || !(parameter->action & COLON_ACTION)))
			return (1);
	return (0);
}
