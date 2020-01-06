/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations1_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 23:42:45 by bmellon           #+#    #+#             */
/*   Updated: 2019/11/11 21:58:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"
#include "ft_printf.h"

extern struct s_op	op_tab[17];

/*
** LIVE 0x01
** renvoie un live pour le processus qui l'appelle
*/

int		op_live(t_param *params, t_process *proc, t_env *e)
{
	t_process	*tail;

	tail = e->proc;
	while (tail)
	{
		if (params[0].value == tail->id)
		{
			e->live_live[tail->pos][0] += 1;
			e->live_live[tail->pos][1] = e->nb_cycles;
			tail->is_alive++;
			e->live.last_id = params[0].value;
			if (tail->file)
				ft_strncpy(e->live.name, ((t_header *)tail->file)->prog_name,
							PROG_NAME_LENGTH + 1);
			break ;
		}
		tail = tail->next;
	}
	e->live_live[proc->pos][0] += 1;
	e->live_live[proc->pos][1] = e->nb_cycles;
	proc->is_alive++;
	print_live(e, params, proc, tail);
	return (0);
}

/*
** DIRECT LOAD 0x02
** load le 1er parametre dans le registre passé en 2nd parametre
** si le 1st param = 0 le carry passe a 1
*/

int		op_ld(t_param *params, t_process *proc, t_env *e)
{
	int		offset;

	if (params[0].type == DIR_CODE)
		*(REG_CAST *)proc->reg[params[1].value - 1] = params[0].value;
	else if (params[0].type == IND_CODE)
	{
		offset = *(REG_CAST *)proc->pc + ((short)params[0].value % IDX_MOD);
		*(REG_CAST *)proc->reg[params[1].value - 1] =
			arena_get(e->arena, offset);
	}
	return (*(REG_CAST *)proc->reg[params[1].value - 1]);
}

/*
** DIRECT STORE 0x03
** inverse de load charge le registre passe en 1st param dans le 2nd param
** meme fonctionnement pour le carry.
**	return (*(REG_CAST *)proc->reg[params[0].value - 1]);
*/

int		op_st(t_param *params, t_process *proc, t_env *e)
{
	int		offset;

	if (params[1].type == REG_CODE)
	{
		*(REG_CAST *)proc->reg[params[1].value - 1] =
		*(REG_CAST *)proc->reg[params[0].value - 1];
	}
	else if (params[1].type == IND_CODE)
	{
		offset = *(REG_CAST *)proc->pc + ((short)params[1].value % IDX_MOD);
		arena_copy(offset, (REG_CAST *)proc->reg[params[0].value - 1],
			proc->color[0], e);
	}
	return (!proc->carry);
}

/*
** ADD 0x04
** ajoute le 1er param et le 2nd et stocke le resultat dans le 3eme
** meme fonctionnement pour le carry
*/

int		op_add(t_param *params, t_process *proc, t_env *e)
{
	int	add;

	(void)e;
	add = *(REG_CAST *)proc->reg[params[0].value - 1]
		+ *(REG_CAST *)proc->reg[params[1].value - 1];
	*(REG_CAST *)proc->reg[params[2].value - 1] = add;
	return (add);
}

/*
** SUB 0x05
** soustraie le 1er param et le 2nd et stocke le resultat dans le 3eme
** meme fonctionnement pour le carry
*/

int		op_sub(t_param *params, t_process *proc, t_env *e)
{
	int	sub;

	(void)e;
	sub = *(REG_CAST *)proc->reg[params[0].value - 1]
		- *(REG_CAST *)proc->reg[params[1].value - 1];
	*(REG_CAST *)proc->reg[params[2].value - 1] = sub;
	return (sub);
}
