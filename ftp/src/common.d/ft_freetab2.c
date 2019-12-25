/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/20 10:42:25 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/12/23 12:21:12 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "common.h"

void			ft_freetab2(char ***tab, int freeall)
{
	int			i;

	i = 0;
	if (!tab || !*tab)
		return ;
	while ((*tab)[i] != 0)
	{
		free((*tab)[i]);
		(*tab)[i] = NULL;
		i++;
	}
	if (freeall)
		free(*tab);
	*tab = NULL;
}
