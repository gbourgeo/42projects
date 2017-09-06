/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_sem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 20:43:10 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/09/06 20:49:42 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/sem.h>
#include <stdio.h>

void				ft_lock(int semid)
{
	struct sembuf	sem;

	sem.sem_num = 0;
	sem.sem_op = -1;
	sem.sem_flg = 0;
	if (semop(semid, &sem, 0) == -1)
		perror("semop_lock");
}


void				ft_unlock(int semid)
{
	struct sembuf	sem;

	sem.sem_num = 0;
	sem.sem_op = 1;
	sem.sem_flg = 0;
	if (semop(semid, &sem, 0) == -1)
		perror("semop_unlock");
}
