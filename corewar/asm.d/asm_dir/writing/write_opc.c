/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_opc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 23:35:31 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/28 23:29:56 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

void	write_opc(t_data *data, int opc)
{
	write(data->fd, &opc, 1);
	if (opc == 1 || opc == 9 || opc == 12 || opc == 15)
		data->encoding_byte = 0;
	else
		data->encoding_byte = 1;
	data->pc = data->pc + 1;
}
