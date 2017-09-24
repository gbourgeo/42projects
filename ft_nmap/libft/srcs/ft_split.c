/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/01 20:05:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/04/21 17:58:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	tab_lines(char *s, char *set)
{
	int		i;
	int		lines;

	i = 0;
	lines = 0;
	while (s[i] != '\0')
	{
		if (ft_strchr(set, s[i]) == NULL)
		{
			lines += 1;
			while (ft_strchr(set, s[i]) == NULL && s[i] != '\0')
				++i;
		}
		else
			++i;
	}
	return (lines);
}

static char	*fill_tab(char *s, char *set)
{
	int		i;
	char	*copy;

	i = 0;
	copy = NULL;
	if (s == NULL)
		return (NULL);
	while (ft_strchr(set, s[i]) == NULL && s[i] != '\0')
		i += 1;
	if ((copy = (char*)malloc(sizeof(copy) * (i + 1))) == NULL)
		return (NULL);
	copy[i] = '\0';
	while (--i >= 0)
		copy[i] = s[i];
	return (copy);
}

char		**ft_split(char *str, char *charset)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	if (str == NULL)
		return (NULL);
	i = tab_lines(str, charset);
	if ((tab = (char**)malloc(sizeof(*tab) * (i + 1))) == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_strchr(charset, str[i]) == NULL)
		{
			tab[j++] = fill_tab(str + i, charset);
			while (ft_strchr(charset, str[i]) == NULL && str[i] != '\0')
				++i;
		}
		else
			++i;
	}
	tab[j] = 0;
	return (tab);
}
