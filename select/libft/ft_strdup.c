/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/20 11:54:28 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/29 00:37:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s1)
{
	int		size;
	char	*dup;

	size = ft_strlen(s1) + 1;
	dup = NULL;
	if ((dup = (char*)malloc(sizeof(*dup) * size)))
	{
		dup[--size] = '\0';
		while (--size >= 0)
			dup[size] = s1[size];
	}
	return (dup);
}
