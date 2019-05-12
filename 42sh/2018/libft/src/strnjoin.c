/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnjoin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 16:35:53 by rfontain          #+#    #+#             */
/*   Updated: 2018/10/25 16:43:04 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*strnjoin(char *str1, char *str2, int n)
{
	char	*dst;
	int		i;
	int		j;

	if (!str1 || !str2)
		return (NULL);
	if (!(dst = (char*)malloc(sizeof(char) * (ft_strlen(str1) + n + 1))))
		return (NULL);
	i = -1;
	while (str1[++i])
		dst[i] = str1[i];
	j = 0;
	while (str2[j] && j < n)
	{
		dst[i + j] = str2[j];
		j++;
	}
	dst[i + j] = '\0';
	return (dst);
}
