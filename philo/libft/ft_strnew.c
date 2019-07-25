/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/26 17:57:53 by ppellegr          #+#    #+#             */
/*   Updated: 2013/11/26 17:57:55 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*allo;
	char	*tmp;

	allo = malloc(size);
	tmp = allo;
	if (allo == NULL)
		return (NULL);
	while (--size)
		*allo++ = '\0';
	return (tmp);
}
