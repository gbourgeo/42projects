/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 19:51:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/01/21 14:51:43 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*p;

	p = NULL;
	len = ft_strlen(s1) + ft_strlen(s2);
	if (len != 0 && (p = (char*)malloc(sizeof(*p) * (len + 1))) != NULL)
	{
		len = 0;
		if (s1)
		{
			while (s1[len])
			{
				p[len] = s1[len];
				++len;
			}
		}
		p = ft_strcat(p, s2);
	}
	return (p);
}
