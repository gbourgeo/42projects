/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beborch <beborch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 23:31:38 by beborch           #+#    #+#             */
/*   Updated: 2017/12/01 01:57:56 by beborch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*s2;

	s2 = (char *)s;
	i = ft_strlen(s2);
	while (i > 0)
	{
		if (s2[i] == c)
		{
			return (s2 + i);
		}
		i--;
	}
	if (i == 0 && s2[i] == c)
	{
		return (s2 + i);
	}
	return (NULL);
}
