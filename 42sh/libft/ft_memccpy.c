/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/01 23:39:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/02 20:16:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void			*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	size_t		i;

	i = 0;
	if ((unsigned char*)s1 == (unsigned char*)s2)
		return (s1);
	while (i < n)
	{
		((unsigned char*)s1)[i] = ((unsigned char*)s2)[i];
		if (((unsigned char*)s2)[i++] == c)
			return (s1 + i);
	}
	return (NULL);
}
