/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/28 00:58:36 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/01/04 04:44:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		tab_line(char const *str, char c);
static int		tab_column(char const *s, char c);
static char		*str_dup(char const *s, char c);

char			**ft_strsplit(char const *s, char c)
{
	int			i;
	int			j;
	char		**tab;

	i = 0;
	j = 0;
	tab = NULL;
	if (s && (tab = (char**)malloc(sizeof(*tab) * (tab_line(&s[i], c)))))
	{
		while (tab_line(&s[i], c) > 1)
		{
			while (s[i] == c && s[i] != '\0')
				++i;
			if (s[i] != '\0')
				tab[j++] = str_dup(&s[i], c);
			while (s[i] != c && s[i] != '\0')
				++i;
		}
		tab[j] = NULL;
	}
	return (tab);
}

static char		*str_dup(char const *s, char c)
{
	char		*cpy;
	int			i;

	i = 0;
	cpy = NULL;
	if (s && (cpy = (char*)malloc(sizeof(*cpy) * tab_column(s, c))))
	{
		while (s[i] != c && s[i] != '\0')
		{
			cpy[i] = s[i];
			++i;
		}
		cpy[i] = '\0';
	}
	return (cpy);
}

static int		tab_column(char const *s, char c)
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
	while (str[i])
	{
		if (str[i] != c)
		{
			while (str[i] != c && str[i] != '\0')
				++i;
			++lin;
		}
		while (str[i] == c && str[i] != '\0')
			++i;
	}
	return (lin + 1);
}
