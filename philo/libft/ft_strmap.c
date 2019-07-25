/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/26 18:06:15 by ppellegr          #+#    #+#             */
/*   Updated: 2013/11/26 18:06:15 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*tmp;
	size_t	i;

	i = 0;
	tmp = NULL;
	if (s == NULL || f == NULL)
		return (NULL);
	tmp = (char *)malloc(ft_strlen(s));
	if (tmp == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		tmp[i] = f(s[i]);
		++i;
	}
	return ((char *)tmp);
}
