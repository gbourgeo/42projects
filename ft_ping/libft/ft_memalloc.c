/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/24 00:47:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/07 19:59:24 by pc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	char	*p;
	size_t	i;

	i = 0;
	if ((p = (char*)malloc(sizeof(*p) * size)) == NULL)
		return (NULL);
	else
		while (i < size)
			p[i++] = 0;
	return (void*)(p);
}
