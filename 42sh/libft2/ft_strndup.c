/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/31 14:54:16 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/01/31 15:11:18 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strndup(const char *s1, int size)
{
	char	*dup;

	dup = NULL;
	if (s1 == NULL || size == 0)
		return (NULL);
	if ((dup = (char*)malloc(sizeof(*dup) * (size + 1))) != NULL)
	{
		dup[size] = '\0';
		while (--size >= 0)
			dup[size] = s1[size];
	}
	return (dup);
}
