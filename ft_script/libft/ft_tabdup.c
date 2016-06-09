/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/28 00:22:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2015/04/04 19:43:45 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_tabdup(char **tab)
{
	char	**cpy;
	int		i;

	cpy = malloc(sizeof(*tab) * (ft_tablen(tab) + 1));
	if (cpy == NULL)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		cpy[i] = ft_strdup(tab[i]);
		i++;
	}
	cpy[i] = 0;
	return (cpy);
}
