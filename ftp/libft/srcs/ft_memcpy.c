/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/23 19:32:45 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/11/28 15:31:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void					*ft_memcpy(void *s1, const void *s2, size_t n)
{
	unsigned char		*t1;
	unsigned const char	*t2;
	size_t				i;

	t1 = s1;
	t2 = s2;
	if (t1 == NULL || t2 == NULL)
		return (NULL);
	else if (n == 0 || t1 == t2)
		return (s1);
	i = 0;
	while (i < n)
	{
		t1[i] = t2[i];
		++i;
	}
	return (s1);
}
