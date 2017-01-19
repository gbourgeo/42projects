/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/01 18:33:18 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/23 21:40:02 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_tabdup(char **tab)
{
	int		i;
	char	**cpy;

	i = 0;
	if (tab == NULL)
		return (NULL);
	while (tab[i] != '\0')
		++i;
	if ((cpy = (char**)malloc(sizeof(*cpy) * i + 1)) == NULL)
		return (NULL);
	i = 0;
	while (tab[i] != '\0')
	{
		if ((cpy[i] = ft_strdup(tab[i])) == NULL)
			break ;
		++i;
	}
	cpy[i] = '\0';
	return (cpy);
}
