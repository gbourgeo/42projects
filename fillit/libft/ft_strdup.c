/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beborch <beborch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 07:29:43 by beborch           #+#    #+#             */
/*   Updated: 2017/12/13 08:58:19 by beborch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (src[i] != '\0')
		i++;
	if (!(str = (char*)malloc(sizeof(*str) * (i + 1))))
		return (NULL);
	while (j < i)
	{
		str[j] = src[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}
