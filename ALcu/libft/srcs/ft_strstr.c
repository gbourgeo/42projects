/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 15:55:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/11 08:07:41 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	int	j;

	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (char*)(s1);
	while (*s1)
	{
		while (s2[j] == s1[j] && s2[j] && s1[j])
			j++;
		if (!s2[j])
			return (char*)(s1);
		j = 0;
		s1++;
	}
	if (!s2[j])
		return (char*)(s1);
	return (NULL);
}
