/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/23 18:17:42 by ppellegr          #+#    #+#             */
/*   Updated: 2013/11/23 18:17:47 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *s1, const void *s2, int c, size_t n)
{
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	while (n--)
	{
		if (*(char *)s2 != (unsigned char)c)
			*(char *)s1++ = *(char *)s2++;
		else
		{
			*(char *)s1++ = *(char *)s2++;
			return (s1);
		}
	}
	return (NULL);
}
