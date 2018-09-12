/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 02:35:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/12 18:06:43 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/sem.h>

void				ft_lock(int semid)
{
	struct sembuf	sem;

	sem.sem_num = 0;
	sem.sem_op = -1;
	sem.sem_flg = 0;
	if (semid != -1)
		semop(semid, &sem, sizeof(sem));
}

void				ft_unlock(int semid)
{
	struct sembuf	sem;

	sem.sem_num = 0;
	sem.sem_op = 1;
	sem.sem_flg = 0;
	if (semid != -1)
		semop(semid, &sem, sizeof(sem));
}
