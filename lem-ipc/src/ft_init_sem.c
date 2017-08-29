/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_sem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 02:35:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/08/29 23:58:32 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "lemipc.h"
#include <sys/sem.h>
#include <stdio.h>
#include <errno.h>

void				ft_lock(void)
{
	struct sembuf	sem;

	e.locked = 1;
	sem.sem_num = 0;
	sem.sem_op = -1;
	sem.sem_flg = 0;
	semop(e.semid, &sem, sizeof(sem));
/* 	if (semop(e.semid, &sem, sizeof(sem)) == 0) */
/* 		perror("semop lock"); */
}

void				ft_unlock(void)
{
	struct sembuf	sem;

	e.locked = 0;
	sem.sem_num = 0;
	sem.sem_op = 1;
	sem.sem_flg = 0;
	semop(e.semid, &sem, sizeof(sem));
/* 	if (semop(e.semid, &sem, sizeof(sem)) == -1) */
/* 		perror("semop unlock"); */
}
