/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 16:42:45 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/01/21 14:52:51 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strcat(char *dest, const char *src)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(dest);
	j = 0;
	if (src)
	{
		while (src[j])
		{
			dest[i + j] = src[j];
			j++;
		}
	}
	dest[i + j] = '\0';
	return (dest);
}
