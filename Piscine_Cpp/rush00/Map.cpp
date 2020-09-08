/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 14:16:24 by gbourgeo          #+#    #+#             */
/*   Updated: 2020/06/05 15:36:17 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Map.hpp"

static int		mystrlen(const char *str)
{
	int		i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

void			printBorder(Screen & screen)
{
	static t_border	left[] = {
		{ "-", mystrlen(left[0].line) },
		{ " |", mystrlen(left[1].line) },
		{ "------", mystrlen(left[2].line) },
		{ "      |", mystrlen(left[3].line) },
		{ "------", mystrlen(left[4].line) },
		{ "   |", mystrlen(left[5].line) },
		{ "---", mystrlen(left[6].line) },
		{ "", mystrlen(left[7].line) },
		{ "--", mystrlen(left[8].line) },
		{ "  |", mystrlen(left[9].line) },
		{ "--", mystrlen(left[10].line) },
	};
	static t_border	right[] = {
		{ "---", mystrlen(right[0].line) },
		{ "|   ", mystrlen(right[1].line) },
		{ "---", mystrlen(right[2].line) },
		{ "|  ", mystrlen(right[3].line) },
		{ "--", mystrlen(right[4].line) },
		{ "|  ", mystrlen(right[5].line) },
		{ "------", mystrlen(right[6].line) },
		{ "|      ", mystrlen(right[7].line) },
		{ "------", mystrlen(right[8].line) },
		{ "|  ", mystrlen(right[9].line) },
		{ "---", mystrlen(right[10].line) },
	};
	static int	i = 0;
	static int first = 0;
	static struct timeval t;
	struct timeval t2;

	wclear(screen.getWindow());
	box(screen.getWindow(), '|', '-');
	if (first == 0)
	{
		gettimeofday(&t, NULL);
		first = 1;
	}
	for (int j = 3, k = i; j < HEIGHT - 1; j++)
	{
		mvwprintw(screen.getWindow(), j, 1, "%s", left[k].line);
		mvwprintw(screen.getWindow(), j, WIDTH - right[k].len - 1, "%s", right[k].line);
		if (--k < 0)
			k = (int)(sizeof(left) / sizeof(left[0])) - 1;
	}
	gettimeofday(&t2, NULL);
	unsigned long time1 = t2.tv_sec * 1000000 - t.tv_sec * 1000000 + t2.tv_usec - t.tv_usec;
	if (time1 >= 100000) {
		gettimeofday(&t, NULL);
		i++;
		if (i >= (int)(sizeof(left) / sizeof(left[0])))
			i = 0;
	}
}

void			printScore(Screen & screen, GameBoard & gameboard, PlayerHandler & players)
{
	double	ret;
	size_t	min;
	size_t	sec;
	unsigned int i;
	Player *p;

	mvwprintw(screen.getWindow(), 1, 1, "SCORE");
	mvwprintw(screen.getWindow(), 1, (WIDTH - 3) / 2, "TIME");
	mvwprintw(screen.getWindow(), 1, (WIDTH - 6), "LIVES");

	i = 1;
	p = players.getPlayer(i);
	while (p)
	{
		mvwprintw(screen.getWindow(), i + 1, 1, "%d", p->getScore());
		i++;
		p = players.getPlayer(i);
	}
	ret = difftime(time(0), gameboard.getTiming());
	min = (size_t)ret / 60;
	sec = (size_t)ret % 60;
	mvwprintw(screen.getWindow(), 2, (WIDTH - 3) / 2, "%ld:%02ld", min, sec);
	i = 1;
	p = players.getPlayer(i);
	while (p)
	{
		mvwprintw(screen.getWindow(), i + 1, (WIDTH - 2), "%d", p->getRetry());
		i++;
		p = players.getPlayer(i);
	}
}
