/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 19:18:35 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/06/26 19:58:20 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	int	i;

	if (s == NULL)
		return (NULL);
	i = ft_strlen(s);
	while (i >= 0 && s[i] != c)
		--i;
	if (i < 0)
		return (NULL);
	return (char*)(s + i);
}
