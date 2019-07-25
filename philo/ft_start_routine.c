/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/11 21:39:36 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/05/12 00:50:51 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		ft_philo_dead(t_philo *philo)
{
	write(1, "The Philosoph ", 14);
	ft_putnbr(philo->i);
	write(1, " is dead !\n", 11);
}

static void		ft_think(t_philo *philo)
{
	if (philo->state != REST && !(pthread_mutex_trylock(philo->stick_left)))
	{
		pthread_mutex_unlock(philo->stick_left);
		philo->state = THINK;
		usleep(THINK_T * 1000000);
	}
	if (philo->state != REST && !(pthread_mutex_trylock(philo->stick_right)))
	{
		pthread_mutex_unlock(philo->stick_right);
		philo->state = THINK;
		usleep(THINK_T * 1000000);
	}
}

static time_t	ft_check_stick(t_philo *philo)
{
	if (!(pthread_mutex_trylock(philo->stick_left)) 
		&& !(pthread_mutex_trylock(philo->stick_right)))
	{
		philo->state = EAT;
		usleep(EAT_T * 1000000);
		philo->life = MAX_LIFE;
		philo->state = REST;
		philo->tloc = time(NULL);
	}
	pthread_mutex_unlock(philo->stick_left);
	pthread_mutex_unlock(philo->stick_right);
	ft_think(philo);
	if (philo->state == REST)
	{
		usleep(REST_T * 1000000);
		philo->state = WAIT;
	}
	return (philo->tloc);
}

static void		ft_check_is_dead(time_t time_t, t_philo *philo)
{
	int			t;

	t = time_t - philo->tloc;
	if (t)
	{
		philo->life -= t;
		if (philo->life <= 0)
		{
			ft_philo_dead(philo);
			philo->tloc = 0;
			return ;
		}
	}
	philo->tloc = time(NULL);
}

void			*ft_start_routine(void *ph)
{
	t_philo		*philo;
	t_div		*env;

	philo = (t_philo*)ph;
	env = (t_div*)philo->divt;
	while (env->start)
		write(1, " ", 0);
	philo->tloc = time(NULL);
	env->countdown = time(NULL);
	while (env->is_dead && env->countdown + TIMEOUT > time(NULL))
	{
		philo->tloc = ft_check_stick(philo);
		ft_check_is_dead(time(NULL), philo);
		if (!philo->tloc)
			break ;
	}
	return (NULL);
}
