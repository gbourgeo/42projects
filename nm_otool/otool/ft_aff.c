/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/04 14:13:50 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/22 01:46:01 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static void				ft_aff_addr(size_t addr, int base, int sector)
{
	int					i;
	int					j;
	char				*hex;
	char				res[base + 1];

	i = base;
	hex = "0123456789abcdef";
	res[base] = '\0';
	while (i-- > 0)
	{
		j = addr % 16;
		res[i] = hex[j];
		addr /= 16;
	}
	write(1, res, base);
	if (sector == DATA_SEC)
		ft_putchar('\t');
	else
		ft_putchar(' ');
}

static void				ft_aff_data(unsigned char value, int base)
{
	int					i;
	int					j;
	char				*hex;
	char				res[base + 1];

	i = base;
	hex = "0123456789abcdef";
	res[base] = '\0';
	while (i-- > 0)
	{
		j = value % 16;
		res[i] = hex[j];
		value /= 16;
	}
	write(1, res, base);
	ft_putchar(' ');
}

void					ft_aff_sf(struct section_64 *sec, char *data, int sect)
{
	uint64_t			i;
	uint64_t			j;
	uint64_t			addr;

	addr = sec->addr;
	i = 0;
	if (sect == TS)
		ft_putendl("(__TEXT,__text) section");
	if (sect == DATA_SEC)
		ft_putendl("(__DATA,__data) section");
	while (i < sec->size)
	{
		ft_aff_addr(addr, 16, sect);
		j = 0;
		while (j < 16 && i + j < sec->size)
		{
			ft_aff_data(*(data + i + j), 2);
			j += sizeof(char);
		}
		i += j;
		addr += j;
		ft_putchar('\n');
	}
}

void					ft_aff_tt(struct section *secz, char *data, int sect)
{
	uint64_t			i;
	uint64_t			j;
	uint64_t			addr;

	addr = secz->addr;
	i = 0;
	if (sect == TS)
		ft_putendl("(__TEXT,__text) section");
	if (sect == DATA_SEC)
		ft_putendl("(__DATA,__data) section");
	while (i < secz->size)
	{
		ft_aff_addr(addr, 8, sect);
		j = 0;
		while (j < 16 && i + j < secz->size)
		{
			ft_aff_data(*(data + i + j), 2);
			j += sizeof(char);
		}
		i += j;
		addr += j;
		ft_putchar('\n');
	}
}
