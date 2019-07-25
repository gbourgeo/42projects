/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/25 19:10:54 by ppellegr          #+#    #+#             */
/*   Updated: 2013/11/25 19:10:56 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*scat;
	int			lengcat;
	char		*tmp;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	lengcat = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	scat = (char *)malloc(sizeof(char) * (lengcat + 1));
	if (scat == NULL)
		return (NULL);
	tmp = scat;
	while (*s1 != '\0')
	{
		*scat = *s1;
		scat++;
		s1++;
	}
	while (*s2 != '\0')
	{
		*scat = *s2;
		scat++;
		s2++;
	}
	*scat = '\0';
	return (tmp);
}
