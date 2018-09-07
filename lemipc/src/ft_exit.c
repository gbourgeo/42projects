/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 23:13:57 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/07 17:30:57 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/sem.h>

void		ft_exit_creation(int print_err, char *err, t_ipc *ipc)
{
	fprintf(stderr, "%s: ", e.prog);
	if (print_err)
		perror(err);
	else
		fprintf(stderr, "%s\n", err);
	if (ipc->msgqid != -1 && msgctl(ipc->msgqid, IPC_RMID, NULL))
		perror("msgctl");
	if (ipc->semid != -1 && semctl(ipc->semid, 0, IPC_RMID))
		perror("semctl");
	if (ipc->board != (void *)-1 && shmdt(ipc->board))
		perror("shmdt");
	if (ipc->shmid != -1 && shmctl(ipc->shmid, IPC_RMID, NULL))
		perror("shmctl");
	ft_memset(ipc, 0, sizeof(*ipc));
	exit(1);
}

void		ft_exit_client(int print_err, char *err, t_ipc *ipc)
{
	fprintf(stderr, "%s: ", e.prog);
	if (print_err)
		perror(err);
	else
		fprintf(stderr, "%s\n", err);
	if (ipc->board != (void *)-1 && shmdt(ipc->board))
		perror("shmdt");
	/* if (e.players) */
	/* 	free(e.players); */
	ft_memset(ipc, 0, sizeof(*ipc));
	exit(1);
}

void		ft_exit(int print_err, char *err)
{
	fprintf(stderr, "%s: ", e.prog);
	if (print_err)
		perror(err);
	else
		fprintf(stderr, "%s\n", err);
	exit(1);
}

/* void		ft_free_exit(t_ipc *ipc) */
/* { */
/* 	if (e.data->connected == 0) */
/* 	{ */
/* 		if (e.msgqid != -1 && msgctl(e.msgqid, IPC_RMID, NULL)) */
/* 			perror("msgctl"); */
/* 		if (e.semid != -1 && semctl(e.semid, 0, IPC_RMID)) */
/* 			perror("semctl"); */
/* 		if (e.shmid != -1) */
/* 		{ */
/* 			if (e.data != (void *)-1 && shmdt(e.data)) */
/* 				perror("shmdt"); */
/* 			if (shmctl(e.shmid, IPC_RMID, NULL)) */
/* 				perror("shmctl"); */
/* 		} */
/* 	} */
/* 	else if (e.data != (void *)-1 && shmdt(e.data) == -1) */
/* 		perror("shmdt"); */
/* 	ft_restore_term(); */
/* 	if (e.players != (void *)-1) */
/* 		free(e.players); */
/* 	ft_bzero(&e, sizeof(e)); */
/* 	exit(0); */
/* } */
