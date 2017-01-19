/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/10 01:16:15 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/09 17:02:44 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_tabdel(char **table)
{
	int			i;

	i = 0;
	if (table)
	{
		while (table[i])
		{
			free(table[i]);
			table[i] = NULL;
			i++;
		}
		free(table);
		table = NULL;
	}
}
