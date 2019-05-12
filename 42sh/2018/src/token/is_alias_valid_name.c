/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_alias_valid_name.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 02:47:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/20 20:34:43 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

int				is_alias_valid_name(const char *alias, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len)
		if (alias[i] != '_' && !ft_isalnum(alias[i]))
			return (0);
		else
			i++;
	return (1);
}
