/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root </var/mail/root>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/22 18:30:37 by root              #+#    #+#             */
/*   Updated: 2016/12/12 11:22:31 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include "libft.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/sem.h>

void		ft_exit_server(int print_err, char *err)
{
	fprintf(stderr, "%s: ", e.prog);
	if (print_err)
		perror(err);
	else
		fprintf(stderr, "%s\n", err);
	if (e.msgqid >= 0 && msgctl(e.msgqid, IPC_RMID, NULL) == -1)
		perror("msgctl");
	if (e.semid >= 0 && semctl(e.semid, 0, IPC_RMID) == -1)
		perror("semctl");
	if (e.shmid >= 0)
	{
		if (e.data != (void *)-1 && shmdt(e.data) == -1)
			perror("shmdt");
		if (shmctl(e.shmid, IPC_RMID, NULL) == -1)
			perror("shmctl");
	}
	ft_restore_term();
	ft_bzero(&e, sizeof(e));
	exit(1);
}

void		ft_exit_client(int print_err, char *err)
{
	fprintf(stderr, "%s: ", e.prog);
	if (print_err)
		perror(err);
	else
		fprintf(stderr, "%s\n", err);
	if (e.data != (void *)-1 && shmdt(e.data) == -1)
		perror("shmdt");
	ft_restore_term();
	ft_bzero(&e, sizeof(e));
	exit(1);
}
