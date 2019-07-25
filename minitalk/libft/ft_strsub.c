/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 19:29:44 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/17 03:26:40 by pc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*p;

	i = 0;
	p = NULL;
	if (s == NULL)
		return (NULL);
	if ((p = (char*)malloc(sizeof(*p) * len + 1)) == NULL)
		return (NULL);
	while (i < len)
	{
		p[i] = s[start + i];
		++i;
	}
	p[i] = '\0';
	return (p);
}
