/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/23 21:55:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/27 19:23:30 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void			*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;

	i = 0;
	if (n && s != NULL)
	{
		while (i < n)
		{
			if ((unsigned char)c == ((unsigned char *)s)[i])
				return ((void *)(s + i));
			++i;
		}
	}
	return (NULL);
}
