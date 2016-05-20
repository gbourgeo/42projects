/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/08/15 06:07:23 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/10 18:38:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void			write_mem_addr(void *zone, char *str)
{
	unsigned long	adr;
	char			*base;
	char			res[5];
	int				i;

	adr = (unsigned long)zone;
	base = "0123456789ABCDEF";
	i = 4;
	if (zone == NULL)
		write(1, "NULL", 4);
	else
	{
		while (i >= 0)
		{
			res[i] = base[adr % 16];
			adr /= 16;
			i--;
		}
		write(1, "0x", 2);
		write(1, res, 5);
	}
	ft_putstr(str);
}

static size_t		write_mem_alloc(t_zone *zone, int reg_size)
{
	size_t			size;
	size_t			i;

	size = 0;
	i = 0;
	if (zone == NULL || zone->data == NULL)
		return (0);
	while (i < zone->size)
	{
		if (*(TYPE *)(zone->data + i) > 0)
		{
			write_mem_addr(zone->data + i + SIZEOF, " - ");
			write_mem_addr(zone->data + (i + SIZEOF +
										*(TYPE *)(zone->data + i)), " : ");
			ft_putnbr(*(TYPE *)(zone->data + i));
			write(1, " octets\n", 8);
			size += *(TYPE *)(zone->data + i);
		}
		i = i + reg_size + SIZEOF;
	}
	if ((size += write_mem_alloc(zone->next, reg_size)) == 0)
		write(1, " Region empty...\n", 17);
	return (size);
}

static size_t		write_large_alloc(t_zone *tmp)
{
	size_t			ret;

	ret = 0;
	while (tmp && tmp->data)
	{
		write_mem_addr(tmp->data, " - ");
		write_mem_addr(tmp->data + tmp->size, " : ");
		ft_putnbr(tmp->size);
		write(1, " octets\n", 8);
		ret += tmp->size;
		tmp = tmp->next;
	}
	return (ret);
}

void				show_alloc_mem(void)
{
	size_t			nb;

	nb = 0;
	write(1, "TINY : ", 7);
	write_mem_addr(mem_list.tiny, "\n");
	nb = write_mem_alloc(mem_list.tiny, TINY);
	write(1, "SMALL : ", 8);
	write_mem_addr(mem_list.small, "\n");
	nb += write_mem_alloc(mem_list.small, SMALL);
	write(1, "LARGE : ", 8);
	write_mem_addr(mem_list.large, "\n");
	nb += write_large_alloc(mem_list.large);
	write(1, "Total : ", 8);
	ft_putnbr(nb);
	write(1, " octets\n", 8);
}
