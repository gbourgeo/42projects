/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/20 23:47:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/05 18:24:34 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free(char ***str)
{
	char	**tab;
	int		i;

	i = 0;
	if (str != NULL)
	{
		tab = *str;
		if (tab != NULL)
		{
			while (tab[i] != NULL)
			{
				free(tab[i]);
				tab[i] = NULL;
				i++;
			}
			free(tab);
			*str = NULL;
		}
	}
}
