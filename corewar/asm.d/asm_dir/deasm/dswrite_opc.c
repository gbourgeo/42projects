/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dswrite_opc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 17:46:50 by mmonier           #+#    #+#             */
/*   Updated: 2019/10/03 17:47:38 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deasm.h"

void		dswrite_opc(t_info *inf, char buff)
{
	static char		*tab[17] = {NULL, "live", "ld", "st", "add", "sub", "and",
								"or", "xor", "zjmp", "ldi", "sti", "fork",
								"lld", "lldi", "lfork", "aff"};
	unsigned int	i;

	i = (unsigned int)buff;
	if (i >= 1 && i <= 16)
	{
		ft_dprintf(inf->ds_fd, "%s\t", tab[i]);
		if ((i >= 1 && i <= 8) || i == 13 || i == 16)
			inf->dir_size = 4;
		else
			inf->dir_size = 2;
	}
}
