/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 23:13:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/07/08 17:19:02 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_fprintf.h"
#include "lemipc.h"

static void	ft_clear_game(void)
{
	if (shmctl(e.game.shmid, IPC_RMID, NULL))
		perror("shmctl");
	e.game.shmid = -1;
	if (shmdt(e.game.board))
		perror("shmdt");
	e.game.board = (void *)-1;
	if (e.game.semid != -1 && semctl(e.game.semid, 0, IPC_RMID))
		perror("semctl");
	e.game.semid = -1;
	if (e.game.msgqid != -1 && msgctl(e.game.msgqid, IPC_RMID, NULL))
		perror("msgctl");
	e.game.msgqid = -1;
}

static int	ft_exit_game(void)
{
	if (e.game.shmid != -1)
	{
		if (e.game.board == (void *)-1)
		{
			if (shmctl(e.game.shmid, IPC_RMID, NULL))
				perror("shmctl");
			e.game.shmid = -1;
		}
		else if (e.game.board->nb_players == 0)
		{
			ft_clear_game();
			return (1);
		}
		if (shmdt(e.game.board))
			perror("shmdt");
		e.game.board = (void *)-1;
	}
	return (0);
}

static void	ft_exit_team(int rm_all)
{
	if (e.teams.shmid != -1)
	{
		if (e.teams.board == (void *)-1)
		{
			if (shmctl(e.teams.shmid, IPC_RMID, NULL))
				perror("shmctl");
			e.teams.shmid = -1;
		}
		else
		{
			if (shmdt(e.teams.board))
				perror("shmdt");
			e.teams.board = (void *)-1;
			if (rm_all)
			{
				if (shmctl(e.teams.shmid, IPC_RMID, NULL))
					perror("shmctl");
				e.teams.shmid = -1;
				if (e.teams.semid != -1 && semctl(e.teams.semid, 0, IPC_RMID))
					perror("semctl");
				e.teams.semid = -1;
			}
		}
	}
}

void		ft_exit_print_winner(int print_err, char *err)
{
	ft_fprintf(stderr, "%s: ", e.prog);
	if (print_err == 0)
		ft_fprintf(stderr, "%s\n", err);
	else if (print_err == 1)
		perror(err);
	else
	{
		if (e.game.board->winner == e.team->uid)
		{
			ft_fprintf(stdout, LEMIPC_WINNING_WORDS, 32, e.game.board->winner);
			ft_fprintf(stdout, "\e[32m ~ VICTORY ~\e[0m\n");
		}
		else
		{
			ft_fprintf(stdout, LEMIPC_WINNING_WORDS, 31, e.game.board->winner);
			ft_fprintf(stdout, "\e[31m ~ DEFEAT ~\e[0m\n");
		}
	}
}

void		ft_exit(int print_err, char *err)
{
	init_signal(SIG_DFL);
	ft_lock(&e.game);
	ft_exit_print_winner(print_err, err);
	if (e.teams.board != (void *)-1 && e.team)
	{
		ft_lock(&e.teams);
		e.team->total--;
		ft_unlock(&e.teams);
	}
	if (e.game.board != (void *)-1)
	{
		*(e.game.map + GET_POS(e.x, e.y)) = MAP_0;
		e.game.board->nb_players--;
	}
	ft_exit_team(ft_exit_game());
	ft_unlock(&e.game);
	if (e.pid)
		waitpid(e.pid, NULL, 0);
	ft_memset(&e, 0, sizeof(e));
	exit(print_err % 2);
}
