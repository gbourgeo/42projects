/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 17:54:52 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/01 21:12:54 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*p;
	unsigned int	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if ((p = ft_strdup(s)) == NULL)
		return (NULL);
	while (s[i])
	{
		p[i] = f(i, s[i]);
		++i;
	}
	return (p);
}
