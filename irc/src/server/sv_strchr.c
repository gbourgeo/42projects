/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 07:18:08 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/04/10 07:24:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char		*sv_strchr(const char *str, int c)
{
	if (!str || !c)
		return (NULL);
	if (c >= 'a' && c <= 'z')
		c -= 32;
	while (*str && *str != c)
		str++;
	return ((*str) ? (char *)str : NULL);
}
