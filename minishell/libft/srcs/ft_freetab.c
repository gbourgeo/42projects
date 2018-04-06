/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 22:46:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/04/05 15:11:49 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void			ft_freetab(char ***table)
{
	char		**ptr;

	if (*table)
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
