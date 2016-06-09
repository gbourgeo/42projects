/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/01 23:39:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2015/02/01 21:50:06 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void			*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	size_t				i;
	unsigned char		*dest;
	const unsigned char	*src;

	i = 0;
	dest = s1;
	src = s2;
	if (dest == src)
		return (s1);
	if (c < 0)
		c = -c;
	while (i < n)
	{
		dest[i] = src[i];
		if (src[i] == c)
			return (&dest[i + 1]);
		i++;
	}
	return (NULL);
}
