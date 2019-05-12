/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_freetab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 11:28:59 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/03/20 21:02:45 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "shell_lib.h"

void			sh_freetab(char ***table)
{
	size_t		i;

	i = 0;
	if (table)
		if (*table)
		{
			while ((*table)[i])
			{
				free((*table)[i]);
				(*table)[i] = NULL;
				i++;
			}
			free(*table);
			*table = (char **)0;
		}
}
