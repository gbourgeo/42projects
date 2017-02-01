/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 04:40:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/30 22:35:00 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			ft_insert_str(char *s1, char *s2, int len)
{
	int			size;

	if (s1 && s2 && len > 0)
	{
		size = ft_strlen(s1);
		while (size--)
			s1[size + len] = s1[size];
		ft_strncpy(s1, s2, len);
	}
}
