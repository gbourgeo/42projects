/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beborch <beborch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 01:25:26 by beborch           #+#    #+#             */
/*   Updated: 2017/11/28 07:10:00 by beborch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int		i;
	unsigned char		*mem;
	const unsigned char	*mem2;

	i = 0;
	mem = (unsigned char*)dest;
	mem2 = (const unsigned char*)src;
	while (i < n)
	{
		mem[i] = mem2[i];
		i++;
	}
	return (dest);
}
