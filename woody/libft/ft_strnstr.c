/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 16:32:39 by gbourgeo          #+#    #+#             */
/*   Updated: 2015/03/27 07:24:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s2[j] == '\0')
		return (char*)(s1);
	while (s1[i] && i < n)
	{
		while (s2[j] && s2[j] == s1[i + j] && (i + j) < n)
			++j;
		if (s2[j] == '\0')
			return (char*)(s1 + i);
		j = 0;
		++i;
	}
	return (NULL);
}
