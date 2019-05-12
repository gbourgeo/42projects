/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 20:04:46 by rfontain          #+#    #+#             */
/*   Updated: 2018/04/05 20:57:25 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*cpy;
	size_t	i;

	cpy = (char*)s;
	i = 0;
	while (i < n)
	{
		if ((unsigned char)cpy[i] == (unsigned char)c)
			return (&cpy[i]);
		i++;
	}
	return (NULL);
}
