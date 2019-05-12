/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 19:14:22 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/05 17:09:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_lib.h"

char			**sh_tabdup(const char **table)
{
	char		**ret;
	size_t		i;

	i = sh_tablen(table);
	if (!(ret = ft_memalloc(sizeof(*ret) * (i + 1))))
		return (NULL);
	i = 0;
	if (!table)
		return (ret);
	while (table[i])
		if (!(ret[i] = ft_strdup(table[i])))
		{
			while (i--)
				free(ret[i]);
			free(ret);
			return (NULL);
		}
		else
			i++;
	return (ret);
}
