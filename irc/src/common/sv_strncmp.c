/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 20:46:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/16 01:19:04 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** sv_strncmp will compare string insensitively 'n' sizely.
*/

#include "libft.h"

int				sv_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!s1 || !s2)
		return (-1);
	while (*s1 && *s2 && n-- > 0 && ft_toupper(*s1) == ft_toupper(*s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
