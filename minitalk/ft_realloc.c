/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/09 19:23:42 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/02/09 19:50:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *src, int size)
{
	char	*new;
	int		len;

	len = 0;
	if (src != NULL)
	{
		while (src[len] != '\0')
			len++;
	}
	if ((new = (char*)malloc(sizeof(char) * (len + size))) != NULL)
	{
		len = 0;
		if (src != NULL)
		{
			while (src[len] != '\0')
			{
				new[len] = src[len];
				len++;
			}
		}
		while (len < size)
			new[len] = '\0';
	}
	return (new);
}
