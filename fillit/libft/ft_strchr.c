/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beborch <beborch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 06:07:52 by beborch           #+#    #+#             */
/*   Updated: 2017/11/29 07:33:02 by beborch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*s2;

	i = 0;
	s2 = (char *)s;
	while (s2[i] != '\0')
	{
		if (s2[i] == c)
			return (&s2[i]);
		i++;
	}
	if (s2[i] == c)
		return (&s2[i]);
	return (NULL);
}
