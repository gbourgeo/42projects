/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 18:38:06 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/11/15 17:15:15 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

static t_bytes	*new_bytes(int offset, short color, int nb_cycle, t_bytes *old)
{
	t_bytes		*new;

	if (!(new = ft_memalloc(sizeof(*new))))
		return (old);
	new->offset = offset;
	new->cycle_to_print = nb_cycle + ARENA_COPY_DURATION;
	new->color = color;
	new->next = old;
	if (old)
		old->prev = new;
	return (new);
}

void			arena_copy(int offset, REG_CAST *value, short color, t_env *e)
{
	uint8_t		*ptr;
	size_t		off;
	size_t		i;

	ptr = (uint8_t *)e->arena;
	i = 0;
	if (!ptr || !value)
		return ;
	off = calc_mod(offset, MEM_SIZE);
	if (e->ncu.active == TRUE)
		e->bytes = new_bytes(off, color, e->nb_cycles, e->bytes);
	while (i++ < REG_SIZE)
	{
		ptr[off] = ((uint8_t *)value)[REG_SIZE - i];
		off = (off + 1) % MEM_SIZE;
	}
	update_aff_arena(offset, REG_SIZE, (short[2]){1, COREWAR_ARENA_COLOR}, e);
}

REG_CAST		arena_get(void *arena, int pc)
{
	char		tab[REG_SIZE];
	uint8_t		*data;
	size_t		offset;
	int			i;

	ft_bzero(tab, REG_SIZE);
	data = (uint8_t *)arena;
	i = 0;
	offset = calc_mod(pc, MEM_SIZE);
	while (i++ < REG_SIZE)
		tab[REG_SIZE - i] = data[(offset + i - 1) % MEM_SIZE];
	return (*(REG_CAST *)tab);
}
