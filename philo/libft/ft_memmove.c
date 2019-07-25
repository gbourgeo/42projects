/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/23 19:32:54 by ppellegr          #+#    #+#             */
/*   Updated: 2013/11/23 19:32:55 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	unsigned char	temp[n];

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	ft_memcpy(temp, s2, n);
	ft_memcpy(s1, temp, n);
	return (s1);
}
