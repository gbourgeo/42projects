/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beborch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 04:30:13 by beborch           #+#    #+#             */
/*   Updated: 2017/11/29 09:56:16 by beborch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned int		i;
	unsigned char		*dest2;
	const unsigned char	*src2;

	i = 0;
	dest2 = (unsigned char*)dest;
	src2 = (const unsigned char *)src;
	if (dest < src)
	{
		while (i < n)
		{
			dest2[i] = src2[i];
			i++;
		}
	}
	else if (dest > src)
	{
		while (n > i)
		{
			dest2[n - 1] = src2[n - 1];
			--n;
		}
	}
	return (dest);
}
