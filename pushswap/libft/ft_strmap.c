/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 17:22:03 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/01 21:11:46 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
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
		p[i] =(*f)(s[i]);
		++i;
	}
	return (p);
}
