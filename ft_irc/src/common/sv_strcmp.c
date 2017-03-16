/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/15 20:33:41 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/15 20:42:32 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** sv_strcmp will compare string insensitively.
*/

#include "libft.h"

int				sv_strcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return (-1);
	while (*s1 && *s2 && ft_toupper(*s1) == ft_toupper(*s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
