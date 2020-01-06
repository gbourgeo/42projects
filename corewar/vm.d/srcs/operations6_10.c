/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations6_10.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 17:51:30 by bmellon           #+#    #+#             */
/*   Updated: 2019/11/12 02:26:51 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "ft_printf.h"

extern struct s_op	op_tab[17];

/*
** AND 0x06
** AND avec le 1er param et le 2nd et stock le resultat dans le 3eme
** meme fonctionnement pour le carry
*/

int		op_and(t_param *params, t_process *proc, t_env *e)
{
	int	calc;

	calc = 0;
	if (params[0].type == REG_CODE)
		calc = *(REG_CAST *)proc->reg[params[0].value - 1];
	else if (params[0].type == DIR_CODE)
		calc = params[0].value;
	else if (params[0].type == IND_CODE)
		calc = arena_get(e->arena, *(REG_CAST *)proc->pc + params[0].value);
	else
		return (calc);
	if (params[1].type == REG_CODE)
		calc &= *(REG_CAST *)proc->reg[params[1].value - 1];
	else if (params[1].type == DIR_CODE)
		calc &= params[1].value;
	else if (params[1].type == IND_CODE)
		calc &= arena_get(e->arena, *(REG_CAST *)proc->pc + params[1].value);
	else
		return (calc);
	*(REG_CAST *)proc->reg[params[2].value - 1] = calc;
	return (calc);
}

/*
** OR 0x07
** OR avec le 1er param et le 2nd et stock le resultat dans le 3eme
** meme fonctionnement pour le carry
*/

int		op_or(t_param *params, t_process *proc, t_env *e)
{
	int	calc;

	calc = 0;
	if (params[0].type == REG_CODE)
		calc = *(REG_CAST *)proc->reg[params[0].value - 1];
	else if (params[0].type == DIR_CODE)
		calc = params[0].value;
	else if (params[0].type == IND_CODE)
		calc = arena_get(e->arena, *(REG_CAST *)proc->pc + params[0].value);
	else
		return (calc);
	if (params[1].type == REG_CODE)
		calc |= *(REG_CAST *)proc->reg[params[1].value - 1];
	else if (params[1].type == DIR_CODE)
		calc |= params[1].value;
	else if (params[1].type == IND_CODE)
		calc |= arena_get(e->arena, *(REG_CAST *)proc->pc + params[1].value);
	else
		return (calc);
	*(REG_CAST *)proc->reg[params[2].value - 1] = calc;
	return (calc);
}

/*
** XOR 0x08
** XOR avec le 1er param et le 2nd et stock le resultat dans le 3eme
** meme fonctionnement pour le carry
*/

int		op_xor(t_param *params, t_process *proc, t_env *e)
{
	int	calc;

	calc = 0;
	if (params[0].type == REG_CODE)
		calc = *(REG_CAST *)proc->reg[params[0].value - 1];
	else if (params[0].type == DIR_CODE)
		calc = params[0].value;
	else if (params[0].type == IND_CODE)
		calc = arena_get(e->arena, *(REG_CAST *)proc->pc + params[0].value);
	else
		return (calc);
	if (params[1].type == REG_CODE)
		calc ^= *(REG_CAST *)proc->reg[params[1].value - 1];
	else if (params[1].type == DIR_CODE)
		calc ^= params[1].value;
	else if (params[1].type == IND_CODE)
		calc ^= arena_get(e->arena, *(REG_CAST *)proc->pc + params[1].value);
	else
		return (calc);
	*(REG_CAST *)proc->reg[params[2].value - 1] = calc;
	return (calc);
}

/*
** ZJMP 0x09
** jump a l'adresse donnee en parametre si le carry est a un, sinon fail
*/

int		op_zjmp(t_param *params, t_process *proc, t_env *e)
{
	(void)e;
	if (proc->carry == 1)
		params[0].size = (short)(params[0].value - 1);
	return (0);
}

/*
** LDI 0x0A
** additione les deux premiers param et va chercher a l'adresse de
** l'addition la valeur a ajouter dans le registre passé en 3eme parametre
** si l'addition = 0 le carry passe a 1
*/

int		op_ldi(t_param *params, t_process *proc, t_env *e)
{
	int			ret;
	int			addr;

	ret = 0;
	if (params[0].type == REG_CODE)
		ret = *(REG_CAST *)proc->reg[params[0].value - 1];
	else if (params[0].type == DIR_CODE)
		ret = params[0].value;
	else if (params[0].type == IND_CODE)
		ret = arena_get(e->arena, *(REG_CAST *)proc->pc + params[0].value);
	else
		return (1);
	if (params[1].type == REG_CODE)
		ret += *(REG_CAST *)proc->reg[params[1].value - 1];
	else if (params[1].type == DIR_CODE)
		ret += params[1].value;
	else
		return (1);
	addr = *(REG_CAST *)proc->pc + ((short)ret % IDX_MOD);
	*(REG_CAST *)proc->reg[params[2].value - 1] = arena_get(e->arena, addr);
	return (1);
}
