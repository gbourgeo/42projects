/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beborch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 03:54:59 by beborch           #+#    #+#             */
/*   Updated: 2017/12/07 03:53:58 by beborch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*str;

	if (!(s1) || !(s2))
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	if (!(str = (char *)ft_memalloc(sizeof(*str) * (i + 1))))
		return (NULL);
	str = ft_strcat(str, (char *)s1);
	str = ft_strcat(str, (char *)s2);
	str[i] = '\0';
	return (str);
}
