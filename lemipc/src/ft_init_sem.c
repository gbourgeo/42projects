/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_sem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 02:35:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/08/30 21:01:45 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/sem.h>

void				ft_lock(int semid)
{
	struct sembuf	sem;

	sem.sem_num = 0;
	sem.sem_op = -1;
	sem.sem_flg = 0;
	semop(semid, &sem, sizeof(sem));
}

void				ft_unlock(int semid)
{
	struct sembuf	sem;

	sem.sem_num = 0;
	sem.sem_op = 1;
	sem.sem_flg = 0;
	semop(semid, &sem, sizeof(sem));
}
