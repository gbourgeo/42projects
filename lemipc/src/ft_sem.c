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

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
void				ft_lock(int semid)
{
	struct sembuf	sem[2];
	int				err;

	if (semid == -1)
		return ;
	// ft_memset(sem, 0, sizeof(*sem));
	sem[0].sem_num = 0;
	sem[0].sem_op = 0;
	sem[0].sem_flg = 0;
	sem[1].sem_num = 0;
	sem[1].sem_op = 1;
	sem[1].sem_flg = 0;
printf("LOCKING...\n");
	if ((err = semop(semid, sem, 2)) != 0)
	{
		printf("ERROR: %d %d\n", err, errno);
		perror("semop");
	}
printf("LOCKED !\n");
}

void				ft_unlock(int semid)
{
	struct sembuf	sem;

	if (semid == -1)
		return ;
	ft_memset(&sem, 0, sizeof(sem));
	sem.sem_num = 0;
	sem.sem_op = -1;
	sem.sem_flg = 0;
write(1, "UNLOCKING...\n", 13);
	semop(semid, &sem, 1);
write(1, "UNLOCKED !\n", 11);
}
