/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 17:37:47 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/14 19:03:58 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_realloc(char *str, size_t size)
{
	char		*new;
	size_t		i;

	new = (char *)malloc(sizeof(*str) * (size + 1));
	if (new == NULL)
		return (NULL);
	ft_bzero(new, size + 1);
	i = 0;
	while (i < size && str && str[i])
	{
		new[i] = str[i];
		i++;
	}
	if (str)
		free(str);
	return (new);
}
