/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/11 23:38:20 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/05/23 19:53:20 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		ft_pthread_create(t_div *divs)
{
	int			i;

	i = 0;
	while (i < NB_PHILOS)
	{
		divs->philo[i].life = MAX_LIFE;
		divs->philo[i].state = WAIT;
		divs->philo[i].i = i;
		divs->philo[i].stick_left = &divs->stick[i];
		if (i == NB_PHILOS - 1)
			divs->philo[i].stick_right = &divs->stick[0];
		else
			divs->philo[i].stick_right = &divs->stick[i + 1];
		divs->philo[i].divt = divs;
		if (!pthread_create(&divs->thread[i], NULL,	ft_start_routine,
							&divs->philo[i]))
		{
			write(1, "Creation du philosophe: ", 24);
			ft_putnbr(i);
			write(1, "\n", 1);
		}
		i++;
	}
}

static void		ft_pthread_mutex_init(t_div *divs)
{
	int			i;

	i = 0;
	while (i < NB_PHILOS)
	{
		if (!pthread_mutex_init(&divs->stick[i], NULL))
		{
			write(1, "Creation de la baguette: ", 25);
			ft_putnbr(i);
			write(1, "\n", 1);
		}
		i++;
	}
}

static void		ft_thread_join(t_div *divs)
{
	int			i;

	i = 0;
	while (i < NB_PHILOS)
	{
		if (!pthread_join(divs->thread[i], NULL))
		{
			ft_putstr("philo[");
			ft_putnbr(i);
			ft_putstr("]: has been JOINED !! ");
		}
		pthread_mutex_unlock(&divs->stick[i]);
		if (!pthread_mutex_destroy(&divs->stick[i]))
		{
			ft_putstr("baguette[");
			ft_putnbr(i);
			ft_putstr("]: has been DESTROYED !!\n");
		}
		i++;
	}
}

int				main(void)
{
	t_div		divs;

	divs.start = 1;
	divs.is_dead = 1;
	ft_pthread_mutex_init(&divs);
	ft_pthread_create(&divs);
	mlx_thread(&divs);
//	usleep(TIMEOUT * 1000000);
	if (divs.is_dead)
		ft_putendl("\nNow, it is time... To DAAAAAAAANCE!!!\n");
	ft_thread_join(&divs);
	return (0);
}
