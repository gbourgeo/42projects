/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/28 00:22:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/20 15:46:00 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_tabdup(const char **table)
{
	char	**cpy;
	int		i;

	cpy = malloc(sizeof(*table) * (ft_tablen(table) + 1));
	if (cpy == NULL)
		return (NULL);
	i = 0;
	while (table && table[i])
	{
		cpy[i] = ft_strdup(table[i]);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}
