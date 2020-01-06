/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naminei <naminei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 03:55:24 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/09 13:30:58 by naminei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "ft_printf.h"

void			dump_map(unsigned char *arena, size_t size)
{
	size_t		i;

	i = 0;
	while (i < size)
	{
		if (i % ARENA_VALUE_PER_LINE == 0)
			ft_printf("0x%04x : ", i);
		ft_printf("%02x ", arena[i]);
		i++;
		if (i % ARENA_VALUE_PER_LINE == 0)
			ft_printf("\n");
	}
}
