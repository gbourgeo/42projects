/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 23:13:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/12 22:17:10 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/wait.h>

static int	ft_exit_game()
{
	if (e.game.shmid != -1)
	{
		if (e.game.board == (void *)-1)
		{
			if (shmctl(e.game.shmid, IPC_RMID, NULL))
				perror("shmctl");
		}
		else if (e.game.board->nb_players-- == 1)
		{
			ft_unlock(e.game.semid);
			if (shmctl(e.game.shmid, IPC_RMID, NULL))
				perror("shmctl");
			if (shmdt(e.game.board))
				perror("shmdt");
			if (e.game.semid != -1 && semctl(e.game.semid, 0, IPC_RMID))
				perror("semctl");
			if (e.game.msgqid != -1 && msgctl(e.game.msgqid, IPC_RMID, NULL))
				perror("msgctl");
			return (0);
		}
		if (shmdt(e.game.board))
			perror("shmdt");
	}
	return (1);
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
			if (rm_all == 0)
			{
				if (shmctl(e.teams.shmid, IPC_RMID, NULL))
					perror("shmctl");
				if (e.teams.semid != -1 && semctl(e.teams.semid, 0, IPC_RMID))
					perror("semctl");
			}
		}
	}
}

void		ft_exit(int print_err, char *err)
{
	fprintf(stderr, "%s: ", e.prog);
	if (print_err)
		perror(err);
	else
		fprintf(stderr, "%s\n", err);
	if (e.game.board != (void *)-1)
	{
		ft_lock(e.game.semid);
		*(e.game.map + GET_POS(e.x, e.y)) = MAP_0;
		ft_unlock(e.game.semid);
	}
	if (e.teams.board != (void *)-1)
	{
		ft_lock(e.teams.semid);
		e.team->total--;
		ft_unlock(e.teams.semid);
	}
	ft_exit_team(ft_exit_game());
	if (e.pid)
	{
		printf("Waiting for game to end...\n");
		waitpid(e.pid, NULL, 0);
	}
	ft_memset(&e, -1, sizeof(e));
	exit(1);
}

void		ft_exit_child(int print_err, char *err)
{
	fprintf(stderr, "%s: ", e.prog);
	if (print_err)
		perror(err);
	else
		fprintf(stderr, "%s\n", err);
	ft_restore_term(&e.term);
	if (e.game.board != (void *)-1)
		shmdt(e.game.board);
	if (e.teams.board != (void *)-1)
		shmdt(e.teams.board);
	exit(1);
}
