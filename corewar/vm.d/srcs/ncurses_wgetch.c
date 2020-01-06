/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_wgetch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 17:34:46 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/11/11 03:46:32 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "libft.h"

static int		ncurses_wgetch_next(t_env *e)
{
	if (e->ch == '+')
	{
		if ((e->speed -= VM_SPEED_RATIO) < 0)
			e->speed = 0;
		if (!e->pause)
			wtimeout(e->ncu.main_win, e->speed);
		return (!e->pause);
	}
	if (e->ch == '-')
	{
		if ((e->speed += VM_SPEED_RATIO) > VM_SPEED_LIMIT)
			e->speed = VM_SPEED_LIMIT;
		if (!e->pause)
			wtimeout(e->ncu.main_win, e->speed);
		return (!e->pause);
	}
	return (0);
}

int				ncurses_wgetch(t_env *e)
{
	if (e->pauses && e->ch == 'p' && e->pauses->cycle_nb > e->nb_cycles)
		return (1);
	e->ch = wgetch(e->ncu.main_win);
	if (e->ch == ERR)
		return ((e->pause) ? ERR : 1);
	if (e->ch == ' ')
	{
		if (!(e->pause = !e->pause))
			wtimeout(e->ncu.main_win, e->speed);
		else
			wtimeout(e->ncu.main_win, -1);
		return (1);
	}
	if (e->ch == 'p')
	{
		if (e->pauses)
		{
			while (e->pauses && e->pauses->cycle_nb <= e->nb_cycles)
				e->pauses = remove_pause(e->pauses);
		}
		return (e->pauses != NULL);
	}
	if (e->ch == 's')
		return (1);
	return (ncurses_wgetch_next(e));
}

int				ncurses_player_calc_x(int id)
{
	char		*nb;
	int			ret;

	if (!(nb = ft_itoa(id)))
		return (100);
	ret = ft_strlen(nb);
	free(nb);
	return (ret);
}
