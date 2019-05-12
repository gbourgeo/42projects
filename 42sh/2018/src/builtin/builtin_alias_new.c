/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias_new.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 23:16:22 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/25 17:47:50 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_env.h"
#include "builtin_alias.h"

t_alias			*alias_new(char *key, char *value, t_alias *prev, t_alias *next)
{
	t_alias		*new;

	if (!(new = ft_memalloc(sizeof(*new))))
		return (NULLALIAS);
	if (key && !(new->key = ft_strdup(key)))
	{
		free(new);
		return (NULLALIAS);
	}
	if (value && alias_set_value(value, new))
	{
		free(new);
		free(new->key);
		return (NULLALIAS);
	}
	new->next = next;
	new->prev = prev;
	if (next)
		next->prev = new;
	if (prev)
		prev->next = new;
	return (new);
}
