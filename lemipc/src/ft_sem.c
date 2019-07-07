/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 02:35:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/07/06 21:36:56 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/sem.h>
#include "libft.h"
#include "lemipc.h"

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
void				ft_lock(void *shm)
{
	t_game			*shared;
	struct sembuf	sem[2];

	shared = (t_game *)shm;
	if (shared->semid == -1 || shared->locked != 0)
		return ;
	// ft_memset(sem, 0, sizeof(*sem));
	sem[0].sem_num = 0;
	sem[0].sem_op = 0;
	sem[0].sem_flg = 0;
	sem[1].sem_num = 0;
	sem[1].sem_op = 1;
	sem[1].sem_flg = 0;
printf("LOCKING...\n");
	if (semop(shared->semid, sem, 2))
		ft_exit(1, "semop (lock)");
	shared->locked = 1;
printf("LOCKED !\n");
}

void				ft_unlock(void *shm)
{
	t_game			*shared;
	struct sembuf	sem;

	shared = (t_game *)shm;
	if (shared->semid == -1 || shared->locked == 0)
		return ;
	ft_memset(&sem, 0, sizeof(sem));
	sem.sem_num = 0;
	sem.sem_op = -1;
	sem.sem_flg = 0;
write(1, "UNLOCKING...\n", 13);
	if (semop(shared->semid, &sem, 1))
		ft_exit(1, "semop (unlock)");
	shared->locked = 0;
write(1, "UNLOCKED !\n", 11);
}
