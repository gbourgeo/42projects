/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_strcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 23:10:16 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/24 14:49:32 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "common.h"

int			ftp_strcmp(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i] && ft_toupper(s1[i]) != ft_toupper(s2[i]))
			return (1);
		i++;
	}
	return (!(s1[i] == s2[i]));
}
