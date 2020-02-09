/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sv_check_err.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 18:30:22 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/02/08 18:33:48 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sv_main.h"

int			sv_check_err(int errnb[], int size)
{
	int		i;

	i = 0;
	while (i < size)
		if (errnb[i] != IS_OK)
			return (0);
		else
			i++;
	return (1);
}
