/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/23 21:55:01 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/05/15 00:17:28 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memmove(void *s1, const void *s2, size_t n)
{
	char		*tone;
	const char	*ttwo;

	tone = s1;
	ttwo = s2;
	tone = ft_strncpy(tone, ttwo, n);
	return (s1);
}
