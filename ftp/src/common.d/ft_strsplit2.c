/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:44:27 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/11/21 19:35:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "common.h"

static int			tab_line(char const *s, char c)
{
	int			total;

	total = 0;
	while (*s)
	{
		while (*s && *s != c)
			s++;
		if (*s == c)
		{
			total++;
			s++;
		}
	}
	return (total);
}

char				**ft_strsplit2(char const *s, char c)
{
	char		**ret;
	char		*ptr;
	int			i;

	if (!s)
		return (NULL);
	if (!(ret = ft_memalloc((tab_line(s, c) + 1) * sizeof(*ret))))
		return (NULL);
	i = 0;
	while (*s)
	{
		if (!(ptr = ft_strchr(s, c)))
			ptr = (char *)s + ft_strlen(s);
		ret[i] = ft_memalloc(ptr - s + 1);
		ft_strncpy(ret[i], s, ptr - s);
		i++;
		s = (*ptr) ? ptr + 1 : ptr;
	}
	return (ret);
}
