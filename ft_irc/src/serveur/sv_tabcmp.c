/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_tabcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 04:43:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/20 05:10:21 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int				sv_tabcmp(char **t1, char **t2)
{
	int			i;

	i = 0;
	if (t1 == NULL || t2 == NULL)
		return (1);
	while (t1[i] && t2[i])
	{
		if (ft_strcmp(t1[i], t2[i]))
			return (1);
		i++;
	}
	if (t1[i] == NULL && t2[i] == NULL)
		return (0);
	return (1);
}
