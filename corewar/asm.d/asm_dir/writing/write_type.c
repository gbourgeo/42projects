/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 23:30:34 by mmonier           #+#    #+#             */
/*   Updated: 2019/10/03 18:04:19 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

static short		set_binary(short bin, int type)
{
	if (type == T_DIR)
	{
		bin = bin << 1;
		bin |= 1;
		bin <<= 1;
	}
	if (type == T_IND)
	{
		bin <<= 1;
		bin |= 1;
		bin <<= 1;
		bin |= 1;
	}
	if (type == T_REG)
	{
		bin <<= 2;
		bin |= 1;
	}
	if (type == 0)
		bin <<= 2;
	return (bin);
}

void				write_type(t_data *data, int *tab)
{
	int		i;
	short	bin;

	i = 0;
	bin = 0x0;
	while (i < 3)
	{
		bin = set_binary(bin, tab[i]);
		i++;
	}
	bin = set_binary(bin, 0);
	write(data->fd, &bin, 1);
	data->pc = data->pc + 1;
}
