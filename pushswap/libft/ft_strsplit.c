/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/28 00:58:36 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/03 23:13:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		tab_line(char const *str, char c);
static	int		tab_column(char const *s, char c);

char			**ft_strsplit(char const *s, char c)
{
	int			i;
	int			j;
	char		**tab;
	char		*tab2;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	if ((tab = (char**)malloc(sizeof(*tab) * (tab_line(s, c)))) == NULL)
		return (NULL);
	if (tab_line(s, c) > 1)
	{
		while (*s == c && *s++) {}
		if (*s != c )
		{
			tab2 = (char*)malloc(sizeof(char) * tab_column(s, c));
			tab[i++] = &tab2[j];
			while (*s != c && *s)
				tab2[j++] = *s++;
			tab2[j++] = '\0';
		}
	}
	tab[i] = '\0';
	return (tab);
}

static	int		tab_column(char const *s, char c)
{
	int			col;

	col = 0;
	while (*s++ != c)
		++col;
	return (col);
}

static	int		tab_line(char const *str, char c)
{
	int			lin;

	lin = 0;
	while (*str)
	{
		if (*str != c && *str)
		{
			while (*str != c && *str++) {}
			++lin;
		}
		while (*str == c && *str++) {}
	}
	return (lin + 1);
}
