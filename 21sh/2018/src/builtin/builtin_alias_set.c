/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias_set.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 23:01:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/25 17:52:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_env.h"
#include "builtin_alias.h"
#include "token.h"

static int		alias_set_key_value(char *key, char *value, t_alias **alias)
{
	t_alias		*ptr;

	ptr = *alias;
	if (!ptr)
		return (!(*alias = alias_new(key, value, *alias, *alias)));
	while (ptr)
	{
		if (ft_strcmp(key, ptr->key) < 0)
		{
			if (!ptr->prev)
				return (!(*alias = alias_new(key, value, ptr->prev, ptr)));
			return (!(ptr = alias_new(key, value, ptr->prev, ptr)));
		}
		if (!ptr->next)
			break ;
		ptr = ptr->next;
	}
	return (!(ptr->next = alias_new(key, value, ptr, ptr->next)));
}

int				alias_set(char *key, t_alias **alias)
{
	char		*value;
	t_alias		*ptr;

	if (!(value = ft_strchr(key, '=')))
		return (1);
	*value++ = '\0';
	ptr = *alias;
	while (ptr)
	{
		if (!ft_strcmp(key, ptr->key))
			return (alias_set_value(value, ptr));
		ptr = ptr->next;
	}
	if (!is_alias_valid_name(key, ft_strlen(key)))
		return (ERR_INVALID_KEY);
	return (alias_set_key_value(key, value, alias));
}
