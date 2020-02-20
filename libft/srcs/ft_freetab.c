/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 22:46:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/13 04:13:03 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void			ft_freetab(char ***table)
{
	char		**ptr;

	if (table && (ptr = *table))
	{
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
