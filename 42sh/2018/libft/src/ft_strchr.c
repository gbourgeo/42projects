/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 22:48:16 by rfontain          #+#    #+#             */
/*   Updated: 2018/04/14 17:51:08 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	*find;

	i = 0;
	find = (char*)str;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (&find[i]);
	return (NULL);
}
