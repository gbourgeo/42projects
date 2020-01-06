/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arena.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 21:02:58 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/11/15 17:14:09 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

int				get_arena(t_env *e)
{
	t_process	*proc;
	size_t		pc;

	proc = e->proc;
	if ((e->arena = ft_memalloc(MEM_SIZE)) == NULL)
		return (ERR_MALLOC);
	pc = 0;
	while (proc)
	{
		ft_memcpy(proc->pc, &pc, REG_SIZE);
		ft_memcpy(proc->reg[0], &proc->id, REG_SIZE);
		ft_memcpy((char *)e->arena + pc,
			(char *)proc->file + sizeof(t_header), proc->data_size);
		proc = proc->next;
		pc += (MEM_SIZE / e->nb_players);
	}
	return (IS_OK);
}
