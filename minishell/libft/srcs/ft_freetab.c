/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 22:46:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/07/12 08:08:36 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void			ft_freetab(char ***table)
{
	char		**ptr;

	if (table == NULL)
		return ;
	ptr = *table;
	if (ptr == NULL)
		return ;
	while (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
		ptr++;
	}
	free(*table);
	*table = NULL;
}
