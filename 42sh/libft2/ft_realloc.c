/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/11 18:09:19 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/13 16:18:12 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_realloc(char *str, int size)
{
	char	*new;
	int		len;

	len = ft_strlen(str);
	if (str == NULL)
		return (NULL);
	if ((new = (char*)malloc(sizeof(char) * (len + size + 1))) == NULL)
		return (NULL);
	ft_bzero(new, len + size + 1);
	new = ft_strcpy(new, str);
	free(str);
	str = NULL;
	return (new);
}
