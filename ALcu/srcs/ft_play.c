/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_play.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naminei <naminei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/09 19:49:02 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/08/02 11:19:04 by naminei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"
#include <stdlib.h>
#include <time.h>

static void		ft_print_info(t_env *e, int player)
{
	static char	*p[] = {
		"Your",
		"Computer",
	};

	ft_putstr(p[player]);
	ft_putendl(" turn to play:");
	ft_print_board(e);
	ft_putstr(p[player]);
	ft_putstr(" move: ");
}

void			ft_play_game(t_env *e)
{
	int			turns;
	int			first;

	turns = 0;
	srand(time(NULL));
	first = rand() % 2;
	if (ft_tgetent(getenv("TERM")))
		return ;
	ft_tputs("cl");
	ft_tputs("sc");
	while (turns < e->x * e->y)
	{
		ft_print_info(e, first);
		first = ft_moves(e, first);
		turns = ft_check_for_a_winner(turns + 1, e);
		ft_tputs("rc");
		ft_tputs("cd");
	}
	ft_print_board(e);
	if (first == PLAYER)
		ft_putendl("COMPUTER WINS ! looser...");
	else
		ft_putendl("OK YOU WON ! lucker...");
}
