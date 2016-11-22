/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 19:51:09 by gbourgeo          #+#    #+#             */
/*   Updated: 2015/03/30 00:11:11 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	char	*p;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	p = ft_strnew(len);
	if (p)
	{
		if (s1)
			p = ft_strcpy(p, s1);
		if (s2)
			p = ft_strcat(p, s2);
	}
	return (p);
}
