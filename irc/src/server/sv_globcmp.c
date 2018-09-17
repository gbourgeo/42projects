/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_globcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 07:20:55 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/11 08:08:38 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			sv_globcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] && s2[i] && s1[i] != '*')
	{
		if (s2[i] != s1[i])
			return (1);
		i++;
	}
	if (s1[i] != '*')
		return (1);
	if (!s1[i + 1] || !s2[i])
		return (0);
	if (ft_strstr(&s2[i], &s1[i + 1]))
		return (0);
	return (1);
}
