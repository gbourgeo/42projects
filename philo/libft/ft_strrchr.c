/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 20:02:16 by ppellegr          #+#    #+#             */
/*   Updated: 2013/11/19 20:02:18 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		j;
	char	*d;

	j = 0;
	if (s == NULL)
		return (NULL);
	if (c < 0 || c > 255)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == c)
		{
			d = ((char *)s);
			j++;
		}
		s++;
	}
	if (j != 0)
		return (d);
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}
