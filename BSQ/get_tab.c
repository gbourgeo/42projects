/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 18:54:36 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/09/15 18:57:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static char	**fill_tab(char *map, char **tab)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	while (map[i])
	{
		if (map[i] == '\n')
		{
			map[i] = '\0';
			if (j == 0)
				len = i;
			tab[j++] = &map[i - len];
		}
		i++;
	}
	tab[j] = NULL;
	return (tab);
}

char		**get_tab(char *map)
{
	char	**tab;
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (map[i])
	{
		if (map[i] == '\n')
			len++;
		i++;
	}
	if ((tab = malloc(sizeof(*tab) * (len + 1))) == NULL)
		return NULL;
	return (fill_tab(map, tab));
}
