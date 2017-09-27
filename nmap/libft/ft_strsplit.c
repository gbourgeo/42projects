/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/28 00:58:36 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/27 19:29:35 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		tab_col(char const *s, char c)
{
	int			col;

	col = 0;
	while (s[col] != c && s[col] != '\0')
		++col;
	return (col + 1);
}

static int		tab_line(char const *str, char c)
{
	int			i;
	int			lin;

	i = 0;
	lin = 0;
	if (str)
	{
		while (str[i] != '\0')
		{
			if (str[i] != c && str[i] != '\0')
			{
				while (str[i] != c && str[i] != '\0')
					++i;
				++lin;
			}
			while (str[i] == c && str[i] != '\0')
				++i;
		}
	}
	return (lin + 1);
}

char			**ft_strsplit(char const *s, char c)
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
	if ((tab = (char**)malloc(sizeof(*tab) * tab_line(s, c))) == NULL)
		return (NULL);
	while (tab_line(&s[i], c) > 1)
	{
		while (s[i] == c && s[i] != '\0')
			++i;
		if ((tab[j] = (char*)malloc(sizeof(char) * tab_col(&s[i], c))) == NULL)
			return (NULL);
		while (s[i] != c && s[i] != '\0')
			tab[j][k++] = s[i++];
		tab[j++][k] = '\0';
		k = 0;
	}
	tab[j] = NULL;
	return (tab);
}
