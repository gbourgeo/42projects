/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/28 00:22:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/05 19:27:19 by gbourgeo         ###   ########.fr       */
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
	while (tab && tab[i])
	{
		cpy[i] = ft_strdup(tab[i]);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}
