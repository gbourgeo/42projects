/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/28 00:22:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/12 17:04:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_tabdup(char **table)
{
	char	**cpy;
	int		i;

	cpy = malloc(sizeof(*table) * (ft_tablen(table) + 1));
	if (cpy == NULL)
		return (NULL);
	i = 0;
	while (table[i])
	{
		cpy[i] = ft_strdup(table[i]);
		i++;
	}
	cpy[i] = 0;
	return (cpy);
}
