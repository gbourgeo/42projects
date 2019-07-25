/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/25 22:46:38 by ppellegr          #+#    #+#             */
/*   Updated: 2013/11/25 22:46:38 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int				i;
	unsigned char	*tmp;

	i = 0;
	if (s == NULL)
		return (NULL);
	tmp = (unsigned char *)s;
	while (n)
	{
		if (tmp[i] == (unsigned char)c)
			return (tmp + i);
		i++;
		n--;
	}
	return (NULL);
}
