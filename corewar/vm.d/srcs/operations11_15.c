/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations11_15.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 18:12:05 by bmellon           #+#    #+#             */
/*   Updated: 2019/11/15 17:14:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "vm.h"

extern struct s_op	op_tab[17];

/*
** STI 0x0B
** additione les deux derniers param et va changer la valeur a l'adresse de
** l'addition avec la valeur dans le registre passé en 1eme parametre
** si l'addition = 0 le carry passe a 1
*/

int		op_sti(t_param *params, t_process *proc, t_env *e)
{
	int		val_a;
	int		val_b;
	int		offset;

	if (params[1].type == REG_CODE)
		val_a = *(REG_CAST *)proc->reg[params[1].value - 1];
	else if (params[1].type == DIR_CODE)
		val_a = params[1].value;
	else if (params[0].type == IND_CODE)
		val_a = arena_get(e->arena, *(REG_CAST *)proc->pc + params[1].value);
	else
		return (!proc->carry);
	if (params[2].type == REG_CODE)
		val_b = *(REG_CAST *)proc->reg[params[2].value - 1];
	else if (params[2].type == DIR_CODE)
		val_b = params[2].value;
	else
		return (!proc->carry);
	if (val_a > USHRT_MAX || val_b > USHRT_MAX)
		offset = *(REG_CAST *)proc->pc + ((val_a + val_b) % IDX_MOD);
	else
		offset = *(REG_CAST *)proc->pc + ((short)(val_a + val_b) % IDX_MOD);
	arena_copy(offset, (REG_CAST *)proc->reg[params[0].value - 1],
		proc->color[0], e);
	return (!proc->carry);
}

/*
** FORK 0x0C
** Cree un nouveau processus
** fork un nouveau processus a l'adresse du premier parametre
** si l'adresse = 0 bah ca boucle du coup
*/

int		op_fork(t_param *params, t_process *proc, t_env *e)
{
	new_proc(proc, params[0].value, 0, e);
	return (!proc->carry);
}

/*
** LLD 0x0D
** direct load sans le %IDX_MOD
** si le 1st param = 0 le carry passe a 1
*/

int		op_lld(t_param *params, t_process *proc, t_env *e)
{
	if (params[0].type == DIR_CODE)
		*(REG_CAST *)proc->reg[params[1].value - 1] = params[0].value;
	else if (params[0].type == IND_CODE)
	{
		params[0].value = *(REG_CAST *)proc->pc + params[0].value;
		*(REG_CAST *)proc->reg[params[1].value - 1] =
		arena_get(e->arena, params[0].value);
	}
	return (*(REG_CAST *)proc->reg[params[1].value - 1]);
}

/*
** LLDI 0x0E
** ldi sans restriction d'adressage
** si l'addition = 0 le carry passe a 1
*/

int		op_lldi(t_param *params, t_process *proc, t_env *e)
{
	int			ret;
	int			offset;

	ret = 0;
	if (params[0].type == REG_CODE)
		ret = *(REG_CAST *)proc->reg[params[0].value - 1];
	else if (params[0].type == DIR_CODE)
		ret = params[0].value;
	else if (params[0].type == IND_CODE)
		ret = arena_get(e->arena, *(REG_CAST *)proc->pc + params[0].value);
	else
		return (*(REG_CAST *)proc->reg[params[2].value - 1]);
	if (params[1].type == REG_CODE)
		ret += *(REG_CAST *)proc->reg[params[1].value - 1];
	else if (params[1].type == DIR_CODE)
		ret += params[1].value;
	else
		return (*(REG_CAST *)proc->reg[params[2].value - 1]);
	offset = *(REG_CAST *)proc->pc + ret;
	*(REG_CAST *)proc->reg[params[2].value - 1] = arena_get(e->arena, offset);
	return (*(REG_CAST *)proc->reg[params[2].value - 1]);
}

/*
** LFORK 0x0F
** fork un nouveau processus a l'adresse du premier parametre
** si l'adresse = 0 bah ca boucle aussi
*/

int		op_lfork(t_param *params, t_process *proc, t_env *e)
{
	new_proc(proc, params[0].value, 1, e);
	return (!proc->carry);
}
