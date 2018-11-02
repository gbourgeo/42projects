/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 11:51:31 by root              #+#    #+#             */
/*   Updated: 2018/10/31 08:10:05 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

extern t_cl	clients[];

void		quitprogram(int signum)
{
	if (signum != SIGINT)
		return ;
	clients[0].leaved = 1;
}

void		changewindow(int signum)
{
	if (signum != SIGWINCH)
		return ;
	endwin();
	refresh();
	clear();
	if (LINES < 24 || COLS < 76)
		termTooSmall();
	else
	{
		createChatBox();
		createUsersBox();
		createTextBox();
		createInfoLine();
	}
}
