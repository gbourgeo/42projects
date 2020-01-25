/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_assign_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 15:31:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/01/25 20:56:05 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

void				sv_assign_ptr(char **ptr, char *assign, char **table)
{
	int			i;
	int			passed;

	i = 0;
	passed = 0;
	ft_strdel(ptr);
	*ptr = assign;
	if (table)
	{
		while (table[i])
		{
			if (table[i] == assign)
				passed = 1;
			else if (passed == 1)
			{
				table[i - 1] = table[i];
				table[i] = NULL;
			}
			i++;
		}
		table[i - 1] = table[i];
	}
}
