/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beborch <beborch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 22:53:49 by beborch           #+#    #+#             */
/*   Updated: 2017/12/29 17:59:39 by beborch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	char	*s;
	size_t	i;

	s = ft_strdup(s1);
	s[n] = '\0';
	if (ft_strstr(s, s2) == NULL)
		return (NULL);
	i = ft_strlen(s) - ft_strlen(ft_strstr(s, s2));
	return ((char *)(unsigned long)(s1 + i));
}
