/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 18:48:48 by ppellegr          #+#    #+#             */
/*   Updated: 2013/11/20 18:48:54 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t		i;
	size_t		j;

	j = 0;
	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (*s2 == '\0')
		return ((char *)s1);
	while (s1[i] != '\0' && i < n)
	{
		while (s1[i + j] == s2[j] && s2[j] != '\0' && (i + j) < n)
			j++;
		if (s2[j] == '\0')
			return ((char*)s1 + i);
		i++;
		j = 0;
	}
	return (NULL);
}
