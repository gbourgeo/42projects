/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrcdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/04 13:51:45 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/02/04 14:06:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strrcdup(char *str, char c)
{
	char		*copy;
	int			i;
	int			len;

	i = 0;
	len = ft_strlen(str);
	if (str == NULL)
		return (NULL);
	while (str[len] != c && len >= 0)
		--len;
	if ((copy = (char*)malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	while (i < len)
	{
		copy[i] = str[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
