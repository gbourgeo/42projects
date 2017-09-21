/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 18:47:34 by gbourgeo          #+#    #+#             */
/*   Updated: 2015/01/29 13:24:49 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int			ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (-1);
	if (n && s1 != s2)
	{
		while (i < n && (unsigned char)s1[i] == (unsigned char)s2[i])
		{
			if (s1[i] == '\0' || s2[i] == '\0')
				return ((unsigned char)s1[i] - (unsigned char)s2[i]);
			++i;
		}
		if (i == n)
			return (0);
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}
