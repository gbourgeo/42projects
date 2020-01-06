/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_aff_update2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 14:42:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/11/11 17:49:13 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			update_aff_process_pc(t_env *e)
{
	t_process	*proc;

	proc = e->proc;
	if (e->ncu.active)
		while (proc)
		{
			update_aff_arena(*(REG_CAST *)proc->pc, 1,
			(short[2]){0, proc->color[1]}, e);
			proc = proc->next;
		}
}

void			update_aff_processes_live(t_process *proc, t_env *e)
{
	int			i;
	int			total;
	int			color;

	i = 0;
	total = 0;
	color = A_BOLD | COLOR_PAIR(COREWAR_CHAMPWIN_COLOR);
	if (e->ncu.active && e->ncu.champ_win)
	{
		wattron(e->ncu.champ_win, color);
		wmove(e->ncu.champ_win, proc->pos_y + 2, 0);
		wclrtoeol(e->ncu.champ_win);
		mvwprintw(e->ncu.champ_win, proc->pos_y + 2, 0, "Processes: %d, "
		"Lives: %d, Last Live: %d", *proc->free_file,
		e->live_live[proc->pos][0], e->live_live[proc->pos][1] + 1);
		wrefresh(e->ncu.champ_win);
		while (i < MAX_PLAYERS)
			total += e->free_file[i++];
		i = e->ncu.winy - 1;
		wmove(e->ncu.champ_win, i, 0);
		wclrtoeol(e->ncu.champ_win);
		mvwprintw(e->ncu.champ_win, i, 0, "Processes: %d", total);
		wattroff(e->ncu.champ_win, color);
		wrefresh(e->ncu.champ_win);
	}
}
