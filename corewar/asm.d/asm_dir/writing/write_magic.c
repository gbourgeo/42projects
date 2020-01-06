/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_magic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmonier <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 21:29:53 by mmonier           #+#    #+#             */
/*   Updated: 2019/09/23 03:13:13 by mmonier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw_hexdump.h"

void		write_magic(t_data *data)
{
	int		magic;

	magic = 0xf383ea;
	lseek(data->fd, 1, SEEK_SET);
	write(data->fd, &magic, 3);
}
