/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/26 15:38:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2015/03/30 00:11:38 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char		*ft_strnew(size_t size)
{
	char	*p;
	size_t	i;

	i = 0;
	p = NULL;
	if ((p = (char*)malloc(sizeof(*p) * size)) == NULL)
		return (NULL);
	while (i < size)
		p[i++] = '\0';
	return (p);
}
