/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 22:50:51 by rfontain          #+#    #+#             */
/*   Updated: 2018/04/13 01:31:34 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*destcp;
	char	*srccp;
	size_t	i;

	destcp = (char*)dest;
	srccp = (char*)src;
	i = 0;
	if (srccp > destcp)
	{
		while (i < n)
		{
			destcp[i] = srccp[i];
			i++;
		}
	}
	else
	{
		while (i < n)
		{
			destcp[n - i - 1] = srccp[n - i - 1];
			i++;
		}
	}
	return (dest);
}
