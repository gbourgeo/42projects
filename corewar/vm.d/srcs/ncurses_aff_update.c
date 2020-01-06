/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_aff_update.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 21:30:31 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/10/15 23:34:52 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

void		update_aff_arena(int offset, int size, short color[2], t_env *e)
{
	size_t	off;
	int		i;
	int		x;
	int		y;

	if (e->ncu.arena_win)
	{
		i = 0;
		off = calc_mod(offset, MEM_SIZE);
		wattron(e->ncu.arena_win, COLOR_PAIR(color[1]));
		while (i++ < size)
		{
			if (color[0])
				e->colors[off] = color[1];
			y = ((off * 3) / ARENA_LINE_LEN) % MEM_SIZE;
			x = ((off * 3) % ARENA_LINE_LEN) % MEM_SIZE;
			mvwprintw(e->ncu.arena_win, y, x, "%02x",
				*((uint8_t *)e->arena + off));
			off = (off + 1) % MEM_SIZE;
		}
		wattroff(e->ncu.arena_win, COLOR_PAIR(color[1]));
		wrefresh(e->ncu.arena_win);
	}
}

void		update_aff_vmstatus(t_env *e)
{
	char	*status[2];

	status[0] = "RUNNING";
	status[1] = "PAUSED";
	if (!e->ncu.vm_win)
		return ;
	if (e->ncu.winx > 6)
	{
		mvwprintw(e->ncu.vm_win, 0, e->ncu.winx / 2 - 6, "** %s **\n",
		status[e->pause]);
		wclrtoeol(e->ncu.vm_win);
		mvwprintw(e->ncu.vm_win, 1, e->ncu.winx / 2 - 7, "speed: %d/%d\n\n",
		VM_SPEED_LIMIT - e->speed, VM_SPEED_LIMIT);
	}
	else
	{
		wprintw(e->ncu.vm_win, "** %s **\n", status[e->pause]);
		wclrtoeol(e->ncu.vm_win);
		wprintw(e->ncu.vm_win, "speed: %d/%d\n\n",
		VM_SPEED_LIMIT - e->speed, VM_SPEED_LIMIT);
	}
}

void		update_aff_vminfo(t_env *e)
{
	if (!e->ncu.vm_win)
		return ;
	wattron(e->ncu.vm_win, A_BOLD);
	wattron(e->ncu.vm_win, COLOR_PAIR(COREWAR_TEXT_COLOR));
	wclrtoeol(e->ncu.vm_win);
	update_aff_vmstatus(e);
	wclrtoeol(e->ncu.vm_win);
	wprintw(e->ncu.vm_win, "Cycle: %d\n\n", e->nb_cycles);
	wclrtoeol(e->ncu.vm_win);
	wprintw(e->ncu.vm_win, "CYCLE_TO_DIE: %d", e->cycle_to_die);
	wattroff(e->ncu.vm_win, COLOR_PAIR(COREWAR_TEXT_COLOR));
	wattroff(e->ncu.vm_win, A_BOLD);
	wrefresh(e->ncu.vm_win);
}

void		update_aff_champion_info(t_op *op, t_param *params,
t_process *proc, t_env *e)
{
	if (!e->ncu.champ_win)
		return ;
	wmove(e->ncu.champ_win, proc->pos_y + 1, 0);
	wattron(e->ncu.champ_win, COLOR_PAIR(COREWAR_CHAMPWIN_COLOR));
	wclrtoeol(e->ncu.champ_win);
	if (op)
	{
		wprintw(e->ncu.champ_win, "\"%s\"", op->reg_name);
		wprintw(e->ncu.champ_win, " p[0]{%d, %#x, %d}", params[0].size,
		params[0].value, params[0].type);
		if (op->reg_nb > 1)
			wprintw(e->ncu.champ_win, ", p[1]{%d, %#x, %d}", params[1].size,
			params[1].value, params[1].type);
		if (op->reg_nb > 2)
			wprintw(e->ncu.champ_win, ", p[2]{%d, %#x, %d}", params[2].size,
			params[2].value, params[2].type);
	}
	mvwprintw(e->ncu.champ_win, proc->pos_y + 1, e->ncu.winx - 8,
		"carry:%d", proc->carry);
	wattroff(e->ncu.champ_win, COLOR_PAIR(COREWAR_CHAMPWIN_COLOR));
	wrefresh(e->ncu.champ_win);
}

void		update_aff_champion_dead(t_env *e, t_process *proc)
{
	if (!e->ncu.champ_win)
		return ;
	update_aff_arena(*(REG_CAST *)proc->pc, 1,
	(short[2]){0, e->colors[*(REG_CAST *)proc->pc]}, e);
	if (*proc->free_file == 1)
	{
		wattron(e->ncu.champ_win, COLOR_PAIR(COREWAR_CHAMPDEAD_COLOR));
		mvwprintw(e->ncu.champ_win, proc->pos_y, e->ncu.winx - 6, "DEAD ");
		wattroff(e->ncu.champ_win, COLOR_PAIR(COREWAR_CHAMPDEAD_COLOR));
	}
}
