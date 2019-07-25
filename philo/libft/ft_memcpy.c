/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 17:19:12 by ppellegr          #+#    #+#             */
/*   Updated: 2013/11/22 17:19:14 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *s1, const void *s2, size_t n)
{
	void	*stmp;

	stmp = s1;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	while (n--)
	{
		*(char *)s1++ = *(char *)s2++;
	}
	return (stmp);
}
