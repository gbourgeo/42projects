/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 03:11:22 by rfontain          #+#    #+#             */
/*   Updated: 2018/10/09 19:44:43 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_countw(const char *str, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		if (str[i] != c && str[i] != '\0')
		{
			count++;
			while (str[i] != c && str[i])
				i++;
		}
	}
	return (count);
}

static	int		ft_strlensp(const char *str, char c)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[j] && str[j] == c)
		j++;
	while (str[j + i] && str[j + i] != c)
		i++;
	return (i);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**split;
	int		k;
	int		nbword;
	int		i;

	if (s == NULL)
		return (NULL);
	if ((split = (char**)malloc(sizeof(char*) * (ft_countw(s, c) + 1))) == NULL)
		return (NULL);
	nbword = ft_countw(s, c);
	k = 0;
	while (nbword--)
	{
		if (!(split[k] = malloc(sizeof(char) * (ft_strlensp(s, c) + 1))))
			return (NULL);
		while (*s && *s == c)
			s++;
		i = 0;
		while (*s != c && *s != '\0')
			split[k][i++] = *s++;
		split[k][i] = '\0';
		k++;
	}
	split[k] = NULL;
	return (split);
}
