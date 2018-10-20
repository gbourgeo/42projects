/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 22:46:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/10/20 16:18:12 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void			ft_freetab(char ***table)
{
	char		**ptr;

	if (table && *table)
	{
		ptr = *table;
		while (*ptr)
		{
			free(*ptr);
			*ptr = NULL;
			ptr++;
		}
		free(*table);
		*table = NULL;
	}
}
