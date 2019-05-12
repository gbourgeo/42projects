/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 03:34:36 by rfontain          #+#    #+#             */
/*   Updated: 2018/04/12 01:50:57 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_strlen_trim(char const *str)
{
	int i;
	int j;

	i = 0;
	j = ft_strlen(str);
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	while (str[j] == ' ' || str[j] == '\t' || str[j] == '\n' || str[j] == '\0')
		j--;
	if (i > j)
		return (0);
	return (ft_strlen(str) - (ft_strlen(str) - j) - i + 1);
}

char			*ft_strtrim(char const *s)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	if (s == NULL)
		return (NULL);
	len = ft_strlen_trim(s);
	if ((str = (char*)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	while (j < len)
	{
		str[j] = s[i + j];
		j++;
	}
	str[j] = '\0';
	return (str);
}
