/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 15:44:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/31 15:50:25 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "common.h"

char			*ft_strcset(char *src, const char *charset)
{
	int		i;
	int		j;

	i = 0;
	if (src && charset)
		while (src[i])
		{
			j = 0;
			while (charset[j])
				if (src[i] == charset[j])
					return (src + i);
				else
					j++;
			i++;
		}
	return (NULL);
}
