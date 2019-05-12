/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_ws.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 07:55:26 by rfontain          #+#    #+#             */
/*   Updated: 2019/03/20 20:07:48 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_countw(const char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && ((str[i] >= 8 && str[i] <= 13) || str[i] == 32))
			i++;
		if (str[i] && !((str[i] >= 8 && str[i] <= 13) || str[i] == 32))
		{
			count++;
			while (str[i] && !((str[i] >= 8 && str[i] <= 13) || str[i] == 32))
				i++;
		}
	}
	return (count);
}

static	int		ft_strlensp(const char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[j] && ((str[j] >= 8 && str[j] <= 13) || str[j] == 32))
		j++;
	while (str[j + i] && !((str[j + i] >= 8 && str[j + i] <= 13)
				|| str[j + i] == 32))
		i++;
	return (i);
}

char			**ft_strsplit_ws(char const *s)
{
	char	**split;
	int		k;
	int		nbword;
	int		i;

	if (s == NULL)
		return (NULL);
	if ((split = (char**)malloc(sizeof(char*) * (ft_countw(s) + 1))) == NULL)
		return (NULL);
	nbword = ft_countw(s);
	k = 0;
	while (nbword--)
	{
		if (!(split[k] = malloc(sizeof(char) * (ft_strlensp(s) + 1))))
			return (NULL);
		while (*s && ((*s >= 8 && *s <= 13) || *s == 32))
			s++;
		i = 0;
		while (*s && !((*s >= 8 && *s <= 13) || *s == 32))
			split[k][i++] = *s++;
		split[k][i] = '\0';
		k++;
	}
	split[k] = NULL;
	return (split);
}
