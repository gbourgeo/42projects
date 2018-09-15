/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beborch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 04:39:49 by beborch           #+#    #+#             */
/*   Updated: 2017/11/28 06:48:41 by beborch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strtb(char *str)
{
	size_t	i;
	size_t	len;
	int		byte;
	char	**tmp;

	if (!str || !*str || !(len = ft_strlen(str)))
		return (NULL);
	if (!(tmp = (char**)malloc(sizeof(char*) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len && (byte = 8))
	{
		if (!(tmp[i] = (char*)malloc(sizeof(char) * 8)))
			return (NULL);
		while (--byte >= 0)
		{
			*tmp[i] = ((*str >> byte) % 2) + 48;
			tmp[i]++;
		}
		tmp[i++] -= 8;
		str++;
	}
	tmp[i] = NULL;
	return (tmp);
}
