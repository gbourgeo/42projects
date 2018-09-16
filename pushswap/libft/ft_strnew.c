/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/26 15:38:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/17 02:52:44 by pc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char		*ft_strnew(size_t size)
{
	char	*p;
	size_t	i;

	i = 0;
	p = NULL;
	if ((p = (char*)malloc(sizeof(char) * (size + 1))) == NULL)
		return (NULL);
	while (i < size + 1)
		p[i++] = '\0';
	return (p);
}
