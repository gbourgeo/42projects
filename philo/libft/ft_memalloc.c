/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/26 17:17:51 by ppellegr          #+#    #+#             */
/*   Updated: 2013/11/26 17:18:00 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char			*alloc;
	char			*tmp;
	size_t			i;

	i = 0;
	alloc = (char *)malloc(sizeof(char) * size);
	if (alloc == NULL)
		return (NULL);
	tmp = alloc;
	while (i < size)
	{
		*alloc++ = 0;
		i++;
	}
	return ((void *)tmp);
}
