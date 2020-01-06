/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_instructions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 17:35:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/11/15 17:14:44 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

extern struct s_op op_tab[17];

static int		instruction_size(t_op *op, t_param *params)
{
	int	i;
	int	len;

	i = 0;
	len = (op->reg_nb == 1 && op->types[0] == T_DIR) ? 1 : 2;
	while (i < op->reg_nb)
	{
		len += params[i].size;
		i++;
	}
	return (len % IDX_MOD);
}

static void		launch_instruction(t_process *proc, t_env *e)
{
	static int	(*instruction_function[])(t_param *, t_process *, t_env *) = {
		op_live, op_ld, op_st, op_add, op_sub, op_and, op_or, op_xor,
		op_zjmp, op_ldi, op_sti, op_fork, op_lld, op_lldi, op_lfork, op_aff,
	};
	t_param		params[MAX_ARGS_NUMBER];
	t_op		*op;
	int			ret;

	ft_bzero(params, sizeof(params));
	op = op_tab + proc->instruction - 1;
	if (get_params(params, op, proc, (uint8_t *)e->arena))
	{
		ret = instruction_function[op->opcode - 1](params, proc, e);
		if (op->modif_carry)
			proc->carry = !ret;
	}
	move_process_pc(proc, instruction_size(op, params), e);
	update_aff_champion_info(op, params, proc, e);
}

size_t			play_instruction(t_process *proc, t_env *e)
{
	if (proc->instruction_wait > (size_t)e->nb_cycles)
		return (0);
	if (proc->instruction_wait == (size_t)e->nb_cycles)
	{
		if (proc->instruction == 0)
		{
			proc->instruction = *((uint8_t *)e->arena +
				*(REG_CAST *)proc->pc);
			if (proc->instruction > 0 && (proc->instruction <
				(uint8_t)(sizeof(op_tab) / sizeof(op_tab[0]))))
				return (op_tab[proc->instruction - 1].cycle - 1);
			else
				move_process_pc(proc, 1, e);
			update_aff_champion_info(NULL, NULL, proc, e);
		}
		else
			launch_instruction(proc, e);
		proc->instruction = 0;
	}
	return (1);
}
