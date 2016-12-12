/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_sem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 02:35:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/12/09 16:36:58 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemipc.h"
#include <sys/sem.h>
#include <stdio.h>

void				ft_lock(void)
{
	struct sembuf	sem;

	sem.sem_num = 0;
	sem.sem_op = -1;
	sem.sem_flg = 0;
	if (semop(e.semid, &sem, 1) == -1)
		perror("semop lock");
}

void				ft_unlock(void)
{
	struct sembuf	sem;

	sem.sem_num = 0;
	sem.sem_op = 1;
	sem.sem_flg = 0;
	if (semop(e.semid, &sem, 1) == -1)
		perror("semop unlock");
}
