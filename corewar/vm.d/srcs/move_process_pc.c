/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_process_pc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 22:54:42 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/19 14:41:37 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "vm_ncurse.h"

REG_CAST		calc_mod(int addr, size_t mod)
{
	while (addr < 0)
		addr += mod;
	return (addr % mod);
}

void			move_process_pc(t_process *proc, int len, t_env *e)
{
	if (e->colors)
		update_aff_arena(*(REG_CAST *)proc->pc, 1,
		(short[2]){0, e->colors[*(REG_CAST *)proc->pc]}, e);
	*(REG_CAST *)proc->pc = calc_mod(*(REG_CAST *)proc->pc + len, MEM_SIZE);
}
