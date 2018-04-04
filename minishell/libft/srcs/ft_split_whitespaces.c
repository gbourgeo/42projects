/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/31 23:26:28 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/30 22:57:22 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	tab_lines(char *s)
{
	int		i;
	int		lines;

	i = 0;
	lines = 0;
	while (s[i] != '\0')
	{
		if (s[i] != ' ' && (s[i] < 9 || s[i] > 11))
		{
			lines += 1;
			while (s[i] != ' ' && (s[i] < 9 || s[i] > 11) && s[i] != '\0')
				++i;
		}
		else
			++i;
	}
	return (lines);
}

static char	*fill_tab(char *str)
{
	int		i;
	char	*copy;

	i = 0;
	copy = NULL;
	if (str == NULL)
		return (NULL);
	while (str[i] != ' ' && (str[i] < 9 || str[i] > 11) && str[i] != '\0')
		i += 1;
	if ((copy = (char*)malloc(sizeof(copy) * (i + 1))) == NULL)
		return (NULL);
	copy[i] = '\0';
	while (--i >= 0)
		copy[i] = str[i];
	return (copy);
}

char		**ft_split_whitespaces(char *str)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	if (str == NULL)
		return (NULL);
	if ((tab = (char**)malloc(sizeof(*tab) * (tab_lines(str) + 1))) == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && (str[i] < 9 || str[i] > 11))
		{
			if ((tab[j++] = fill_tab(str + i)) == NULL)
				break ;
			while (str[i] != ' ' && (str[i] < 9 || str[i] > 11) && str[i])
				++i;
		}
		else
			++i;
	}
	tab[j] = NULL;
	return (tab);
}
