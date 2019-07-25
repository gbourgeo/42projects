/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/26 18:34:39 by ppellegr          #+#    #+#             */
/*   Updated: 2013/11/26 18:34:42 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strlen_lnum(char const *s, char c, int k)
{
	int		i;

	i = 0;
	while (s[k] != c && s[k] != '\0')
	{
		++k;
		++i;
	}
	return (i);
}

int		ft_strlen_wnum(char const *s, char c)
{
	int		k;
	int		i;

	k = 0;
	i = 0;
	while (s[k] != '\0')
	{
		while (s[k] == c)
			k++;
		if (s[k] == '\0')
			break ;
		while (s[k] != c && s[k] != '\0')
			k++;
		i++;
	}
	return (i);
}

char	**ft_strsplit(char const *s, char c)
{
	char	**new_strs;
	int		i;
	int		j;
	int		k;
	int		wnum;

	i = 0;
	k = 0;
	wnum = ft_strlen_wnum(s, c);
	if (s == NULL || (!(new_strs = malloc(sizeof(char *) * (wnum + 1)))))
		return (NULL);
	while (wnum--)
	{
		j = 0;
		if ((!(new_strs[i] = malloc(ft_strlen_lnum(s, c, k) + 1))))
			return (NULL);
		while (s[k] == c)
			k++;
		while (s[k] != c && s[k] != '\0')
			new_strs[i][j++] = s[k++];
		new_strs[i++][j] = '\0';
	}
	new_strs[i] = NULL;
	return (new_strs);
}
