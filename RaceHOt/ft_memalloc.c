/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/14 21:17:04 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/14 21:20:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void		*ft_memalloc(size_t size)
{
	char	*p;
	size_t	i;

	p = NULL;
	i = 0;
	if ((p = (char*)malloc(sizeof(*p) * size + 1)) == NULL)
		return (NULL);
	while (i < size)
		p[i++] = 0;
	return (void*)(p);
}
