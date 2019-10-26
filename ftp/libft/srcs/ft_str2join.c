/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str2join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/23 05:43:22 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/04/21 18:03:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_str2join(char const *s1, char const *s2, char const *s3)
{
	int		len;
	char	*p;

	p = NULL;
	len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
	if ((p = (char*)malloc(sizeof(*p) * (len + 1))) != NULL)
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
		p[len] = '\0';
		p = ft_strcat(p, s2);
		p = ft_strcat(p, s3);
	}
	return (p);
}
