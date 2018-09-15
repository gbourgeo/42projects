/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beborch <beborch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 02:23:23 by beborch           #+#    #+#             */
/*   Updated: 2017/11/28 06:55:30 by beborch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned int			i;
	unsigned char			*dest2;
	const unsigned char		*src2;

	i = 0;
	dest2 = (unsigned char*)dest;
	src2 = (const unsigned char*)src;
	while (i < n)
	{
		dest2[i] = src2[i];
		if (src2[i] == (unsigned char)c)
			return (&dest[i + 1]);
		i++;
	}
	return (NULL);
}
