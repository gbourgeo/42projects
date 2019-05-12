/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias_set_value.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 04:26:17 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/02/19 03:11:12 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_env.h"
#include "builtin_alias.h"

int				alias_set_value(char *value, t_alias *alias)
{
	char		*save;

	save = alias->value;
	if (!(alias->value = ft_memalloc(ft_strlen(value) + 1)))
	{
		alias->value = save;
		return (ERR_MALLOC);
	}
	ft_strcpy(alias->value, value);
	if (save)
		free(save);
	return (ERR_OK);
}
