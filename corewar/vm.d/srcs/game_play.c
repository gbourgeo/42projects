/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_play.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 23:05:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/11/11 04:21:06 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

static void		check_live_total(size_t nb_alive, t_env *e)
{
	if (nb_alive >= NBR_LIVE)
	{
		if ((e->cycle_to_die = e->cycle_to_die - CYCLE_DELTA) < 0)
			e->cycle_to_die = 0;
		update_aff_vminfo(e);
	}
}

static void		check_max_checks(t_env *e)
{
	if (++(e->checks) == MAX_CHECKS)
	{
		if ((e->cycle_to_die = e->cycle_to_die - CYCLE_DELTA) < 0)
			e->cycle_to_die = 0;
		e->checks = 0;
		update_aff_vminfo(e);
	}
}

static size_t	check_players_alive(t_env *e)
{
	t_process	*proc;
	size_t		alive;

	alive = 0;
	proc = e->proc;
	while (proc)
	{
		if (!proc->is_alive)
		{
			update_aff_champion_dead(e, proc);
			if (!(proc = remove_proc(&proc, e)))
				break ;
		}
		else
		{
			alive += proc->is_alive;
			proc->is_alive = 0;
			proc = proc->next;
		}
	}
	check_live_total(alive, e);
	check_max_checks(e);
	ft_bzero(e->live_live, sizeof(e->live_live));
	e->last_cycle_to_die = e->nb_cycles + 1;
	return (alive);
}

int				play_game(t_env *e)
{
	t_process	*proc;

	if (e->dump_cycle == e->nb_cycles)
		return (-3);
	if (!e->cycle_to_die)
		return (-2);
	proc = e->proc;
	while (proc)
	{
		proc->instruction_wait += play_instruction(proc, e);
		proc = proc->next;
	}
	if (e->nb_cycles - e->last_cycle_to_die + 1 >= e->cycle_to_die)
		if (!check_players_alive(e))
			return (-2);
	return (0);
}
