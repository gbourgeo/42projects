/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_aff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 16:47:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/11/11 03:31:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** size_t i[2] :
** i[0] : arena iteration counter
** i[1] : arena color offset
**
** char flag[2] :
** flag[0] : Did we changed the color ?
** flag[1] : Did we changed process ?
*/

static void		ncurses_aff_arena(t_env *e)
{
	size_t		i;
	t_process	*proc;
	short		color;

	i = 0;
	color = 0;
	while (i < MEM_SIZE)
	{
		wattron(e->ncu.arena_win, COLOR_PAIR(e->colors[i]));
		if ((proc = e->proc))
			while (proc)
			{
				if (*(REG_CAST *)proc->pc == i && (color = proc->color[i]))
					wattron(e->ncu.arena_win, COLOR_PAIR(proc->color[1]));
				proc = proc->next;
			}
		wprintw(e->ncu.arena_win, "%02x", *((unsigned char *)e->arena + i));
		wattron(e->ncu.arena_win, COLOR_PAIR(COREWAR_DFLT_COLOR));
		if (++i % ARENA_VALUE_PER_LINE != 0)
			wprintw(e->ncu.arena_win, " ");
		wattroff(e->ncu.arena_win, COLOR_PAIR(e->colors[i - 1]));
		wattroff(e->ncu.arena_win, COLOR_PAIR(color));
		wattroff(e->ncu.arena_win, COLOR_PAIR(COREWAR_DFLT_COLOR));
	}
	wrefresh(e->ncu.arena_win);
}

/*
** players = 1, y1 = -1
** players = 2, y1 = -2, y2 = 1
** players = 3, y1 = -4, y2 = -1, y3 = 3
** players = 4, y1 = -6, y2 = -3, y3 = 0, y4 = 3
*/

static void		ncurses_aff_champion_info(t_process *proc, t_env *e)
{
	t_header	*play;
	int			x;

	if (!e->ncu.champ_win)
		return ;
	play = (t_header *)proc->file;
	x = ncurses_player_calc_x(proc->id) + 10;
	proc->pos_y = (e->ncu.winy / 2) + (((e->nb_players * 3)) / 2) - 2;
	proc->pos_y -= proc->pos * 4;
	wattron(e->ncu.champ_win, COLOR_PAIR(proc->color[1]));
	mvwprintw(e->ncu.champ_win, proc->pos_y, 0, "Player %d ", proc->id);
	wattroff(e->ncu.champ_win, COLOR_PAIR(proc->color[1]));
	wattron(e->ncu.champ_win, COLOR_PAIR(COREWAR_CHAMPWIN_COLOR));
	mvwprintw(e->ncu.champ_win, proc->pos_y, x, "\"%s\"", play->prog_name);
	wattroff(e->ncu.champ_win, COLOR_PAIR(COREWAR_CHAMPWIN_COLOR));
	wattron(e->ncu.champ_win, COLOR_PAIR(COREWAR_CHAMPALIVE_COLOR));
	mvwprintw(e->ncu.champ_win, proc->pos_y, e->ncu.winx - 6, "ALIVE");
	wattroff(e->ncu.champ_win, COLOR_PAIR(COREWAR_CHAMPALIVE_COLOR));
	mvwprintw(e->ncu.champ_win, proc->pos_y + 2, 0, "Processes: %d, Lives: %d,"
	" Last Live: %d", *proc->free_file, e->live_live[proc->pos][0],
	e->live_live[proc->pos][1]);
}

static void		ncurses_aff_champion(t_env *e)
{
	t_process	*proc;

	if (!e->ncu.champ_win)
		return ;
	wclear(e->ncu.champ_win);
	wattron(e->ncu.champ_win, A_BOLD);
	proc = e->proc;
	while (proc)
	{
		if (proc->file)
			ncurses_aff_champion_info(proc, e);
		proc = proc->next;
	}
	wattroff(e->ncu.champ_win, A_BOLD);
	wrefresh(e->ncu.champ_win);
}

static void		ncurses_aff_vminfo(t_env *e)
{
	if (!e->ncu.vm_win)
		return ;
	wattron(e->ncu.vm_win, A_BOLD);
	wattron(e->ncu.vm_win, COLOR_PAIR(COREWAR_TEXT_COLOR));
	update_aff_vmstatus(e);
	wprintw(e->ncu.vm_win, "Cycle: %d\n\n", e->nb_cycles);
	wprintw(e->ncu.vm_win, "CYCLE_TO_DIE: %d\n\n", e->cycle_to_die);
	wprintw(e->ncu.vm_win, "CYCLE_DELTA: %d\n\n", CYCLE_DELTA);
	wprintw(e->ncu.vm_win, "NBR_LIVE: %d\n\n", NBR_LIVE);
	wprintw(e->ncu.vm_win, "MAX_CHECKS: %d", MAX_CHECKS);
	wattroff(e->ncu.vm_win, COLOR_PAIR(COREWAR_TEXT_COLOR));
	wattroff(e->ncu.vm_win, A_BOLD);
	wrefresh(e->ncu.vm_win);
}

void			ncurses_aff_all(t_env *e)
{
	if (e->ncu.active == FALSE)
		return ;
	if (e->ncu.arena_win && e->arena && e->colors)
		ncurses_aff_arena(e);
	ncurses_aff_champion(e);
	ncurses_aff_vminfo(e);
}
