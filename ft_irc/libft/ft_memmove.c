/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/23 21:55:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2013/12/01 20:56:50 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memmove(void *s1, const void *s2, size_t n)
{
	char		*tone;
	const char	*ttwo;

	tone = s1;
	ttwo = ft_strdup(s2);
	if (tone == ttwo)
		return (s1);
	tone = ft_strncpy(tone, ttwo, n);
	return (s1);
}
