/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naminei <naminei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 02:35:51 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/07/08 15:43:33 by naminei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <sys/sem.h>
#include "libft.h"
#include "lemipc.h"

int				ft_lock(void *shm)
{
	t_game			*shared;
	struct sembuf	sem;
	int				ret;

	shared = (t_game *)shm;
	if (shared->semid == -1 || shared->locked != 0)
		return (0);
	sem.sem_num = 0;
	sem.sem_op = -1;
	sem.sem_flg = IPC_NOWAIT;
	if ((ret = semop(shared->semid, &sem, 1)))
	{
		if (ret == EAGAIN)
			return (0);
		ft_exit(1, "semop (lock)");
	}
	shared->locked = 1;
	return (1);
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
	sem.sem_op = 1;
	sem.sem_flg = 0;
	if (semop(shared->semid, &sem, 1))
		ft_exit(1, "semop (unlock)");
	shared->locked = 0;
}
