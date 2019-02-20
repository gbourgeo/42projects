/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strangesplit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/16 18:48:00 by gbourgeo          #+#    #+#             */
/*   Updated: 2015/02/24 11:33:21 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		tab_col(char const *str)
{
	int			i;

	i = 0;
	while (((str[i] >= '0' && str[i] <= '9') || str[i] == '-') && str[i])
		++i;
	return (i + 1);
}

static int		tab_line(char const *str)
{
	int			i;
	int			lin;

	i = 0;
	lin = 0;
	if (str)
	{
		while (str[i] != '\0')
		{
			if ((str[i] >= '0' && str[i] <= '9') || str[i] == '-')
			{
				while (((str[i] >= '0' && str[i] <= '9') || str[i] == '-')
						&& str[i] != '\0')
					++i;
				++lin;
			}
			while ((str[i] < '0' || str[i] > '9') && str[i] != '-'
					&& str[i] != '\0')
				++i;
		}
	}
	return (lin + 1);
}

char			**ft_strangesplit(char const *s)
{
	int			i;
	int			j;
	int			k;
	char		**tab;

	i = 0;
	j = 0;
	k = 0;
	if (s == NULL)
		return (NULL);
	if ((tab = (char**)malloc(sizeof(*tab) * tab_line(s))) == NULL)
		return (NULL);
	while (tab_line(&s[i]) > 1)
	{
		while ((s[i] < '0' || s[i] > '9') && s[i] != '-' && s[i] != '\0')
			++i;
		if ((tab[j] = (char*)malloc(sizeof(char) * tab_col(&s[i]))) == NULL)
			return (NULL);
		while (((s[i] >= '0' && s[i] <= '9') || s[i] == '-') && s[i] != '\0')
			tab[j][k++] = s[i++];
		tab[j++][k] = '\0';
		k = 0;
	}
	tab[j] = NULL;
	return (tab);
}
