/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/22 15:55:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/11/27 21:31:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s2[j] == '\0')
		return (char*)(s1);
	while (s1[i])
	{
		while (s2[j] == s1[i + j] && (s2[j] || s1[i + j]))
			++j;
		if (s2[j] == '\0')
			return (char*)(s1 + i);
		j = 0;
		++i;
	}
	return (NULL);
}
