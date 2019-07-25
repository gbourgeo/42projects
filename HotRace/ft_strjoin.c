/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/14 22:57:17 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/15 13:05:18 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	count_lenght(const char *str);

char		*ft_strjoin(char const *s1, char const*s2)
{
	char	*p;
	size_t	len;
	size_t	i;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = count_lenght(s1) + count_lenght(s2) + 1;
	if ((p = (char*)malloc(sizeof(char) * len)) == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		++i;
	}
	j = 0;
	while (s2[j])
	{
		p[i + j] = s2[j];
		++j;
	}
	p[i + j] = '\0';
	return (p);
}

static int	count_lenght(const char *str)
{
	int		i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}
