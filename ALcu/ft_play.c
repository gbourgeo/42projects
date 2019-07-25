/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_play.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/09 19:49:02 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/10 06:45:34 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alcu.h"
#include <stdlib.h>
#include <time.h>

void			ft_play_game(t_env *e)
{
	int			turns;
	int			first;

	turns = 0;
	srand(time(NULL));
	if (rand() % 2)
		first = ft_player_shot(e);
	else
		first = ft_computer_shot(e);
	while (turns <= 42)
	{
		if (first == PLAYER && ++turns)
			first = ft_player_shot(e);
		if (first == COMPUT && ++turns)
			first = ft_computer_shot(e);
		if (turns >= 6)
			turns = ft_check_for_a_winner(turns, e);
	}
	if (first == PLAYER)
		ft_putendl("COMPUTER WINS ! looser...");
	else
		ft_putendl("OK YOU WON ! lucker...");
}

void		ft_print_info(char **board, int player)
{
	if (player == PLAYER)
	{
		ft_putendl("Your turn to play:");
		ft_print_board(board);
		ft_putstr("Your Move: ");
	}
	if (player == COMPUT)
	{
		ft_putendl("Computer turn to play:");
		ft_print_board(board);
		ft_putstr("Computer Move: ");
	}
}

void		ft_print_board(char **board)
{
	int			i;
	int			j;

	i = 0;
	while (board[i])
	{
		j = 0;
		while (board[i][j])
		{
			ft_putchar('|');
			ft_putchar(board[i][j++]);
		}
		ft_putstr("|\n");
		i++;
	}
}
