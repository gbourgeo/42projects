/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 02:35:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/05/28 17:02:00 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/sem.h>
#include "libft.h"

void				ft_lock(int semid)
{
	struct sembuf	sem;

	if (semid == -1)
		return ;
	ft_memset(&sem, 0, sizeof(sem));
	sem.sem_num = 0;
	sem.sem_op = -1;
	sem.sem_flg = 0;
	semop(semid, &sem, sizeof(sem));
}

void				ft_unlock(int semid)
{
	struct sembuf	sem;

	if (semid == -1)
		return ;
	ft_memset(&sem, 0, sizeof(sem));
	sem.sem_num = 0;
	sem.sem_op = 1;
	sem.sem_flg = 0;
	semop(semid, &sem, sizeof(sem));
}
