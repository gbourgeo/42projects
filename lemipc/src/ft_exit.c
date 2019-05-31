/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 23:13:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/05/28 16:55:11 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include "lemipc.h"
#include "libft.h"
#include "ft_fprintf.h"

static int	ft_exit_game(void)
{
	if (e.game.shmid != -1)
	{
		if (e.game.board == (void *)-1)
		{
			if (shmctl(e.game.shmid, IPC_RMID, NULL))
				perror("shmctl");
		}
		else if (e.game.board->nb_players == 0)
		{
			if (shmctl(e.game.shmid, IPC_RMID, NULL))
				perror("shmctl");
			if (shmdt(e.game.board))
				perror("shmdt");
			if (e.game.semid != -1 && semctl(e.game.semid, 0, IPC_RMID))
				perror("semctl");
			if (e.game.msgqid != -1 && msgctl(e.game.msgqid, IPC_RMID, NULL))
				perror("msgctl");
			return (1);
		}
		if (shmdt(e.game.board))
			perror("shmdt");
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
		}
		else
		{
			if (shmdt(e.teams.board))
				perror("shmdt");
			if (rm_all)
			{
				if (shmctl(e.teams.shmid, IPC_RMID, NULL))
					perror("shmctl");
				if (e.teams.semid != -1 && semctl(e.teams.semid, 0, IPC_RMID))
					perror("semctl");
			}
		}
	}
}

static void	ft_exit_print_winner(int print_err, char *err)
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

void		ft_exit(int print_err, char *err, int locked)
{
	init_signal(SIG_DFL);
	if (!locked)
		ft_lock(e.game.semid);
	ft_exit_print_winner(print_err, err);
	if (e.teams.board != (void *)-1 && e.team)
	{
		ft_lock(e.teams.semid);
		e.team->total--;
		ft_unlock(e.teams.semid);
	}
	if (e.game.board != (void *)-1)
	{
		*(e.game.map + GET_POS(e.x, e.y)) = MAP_0;
		e.game.board->nb_players--;
	}
	ft_exit_team(ft_exit_game());
	ft_unlock(e.game.semid);
	if (e.pid)
		waitpid(e.pid, NULL, 0);
	ft_memset(&e, 0, sizeof(e));
	exit(print_err % 2);
}

void		ft_exit_child(int print_err, char *err)
{
	ft_exit_print_winner(print_err, err);
	ft_restore_term(&e.term);
	if (e.game.board != (void *)-1)
		shmdt(e.game.board);
	if (e.teams.board != (void *)-1)
		shmdt(e.teams.board);
	exit(1);
}
