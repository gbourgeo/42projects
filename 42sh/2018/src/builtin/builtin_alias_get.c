/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias_get.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 05:26:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/21 05:22:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "builtin_alias.h"

static int		alias_strncmp(const char *s1, const char *s2, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len && s1[i] == s2[i])
		i++;
	return (!(i == len && s2[i] == '\0'));
}

t_alias			*alias_get(const char *str, size_t len, t_alias *alias)
{
	if (!str || !alias || len == 0)
		return (NULLALIAS);
	while (alias)
	{
		if (!alias->in_use && !alias_strncmp(str, alias->key, len))
			return (alias);
		alias = alias->next;
	}
	return (NULLALIAS);
}
