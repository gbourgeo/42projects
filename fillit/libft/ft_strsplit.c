/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beborch <beborch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/18 02:37:29 by beborch           #+#    #+#             */
/*   Updated: 2017/12/29 18:00:56 by beborch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_words(char const *s, char c)
{
	size_t	w;

	w = 0;
	while (s && *s)
	{
		while (*s == c)
			s++;
		while (*s != c && *s)
			s++;
		w++;
	}
	return (w);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	i;
	int		n;
	char	**rslt;
	char	*tmp;

	n = 0;
	if ((rslt = (char **)malloc(sizeof(char *) * (ft_words(s, c) + 1))) == NULL)
		return (NULL);
	while (s && *s)
	{
		i = 0;
		while (*s == c)
			s++;
		while (s[i] != c && s[i])
			i++;
		if ((tmp = ft_strnew(i + 1)) == NULL)
			return (NULL);
		if ((s[i] == '\0' || s[i] == c) && i)
			rslt[n++] = ft_strncpy(tmp, s, i);
		s += i;
	}
	rslt[n] = NULL;
	return (rslt);
}
