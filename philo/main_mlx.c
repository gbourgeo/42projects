/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/11 19:25:13 by ppellegr          #+#    #+#             */
/*   Updated: 2014/05/11 19:25:15 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "mlx_philo.h"

void		mlx_thread(t_div *divs)
{
	pthread_create(&divs->thread[NB_PHILOS], NULL, mlx, divs);
	divs->start = 0;
}

void		*mlx(void *tmp)
{
	t_env			*e;
	struct s_div	*divs;

	divs = (struct s_div*)tmp;
	e = (t_env *)malloc(sizeof(t_env));
	e->divs = divs;
	init_mlx(e);
	e->mlx = mlx_init();
	if (e->mlx != NULL)
	{
		e->win = mlx_new_window(e->mlx, e->win_x, e->win_y, "Diner Philo");
		mlx_key_hook(e->win, key_hook, e);
		mlx_expose_hook(e->win, expose_hook, e);
		mlx_loop_hook(e->mlx, draw, e);
		mlx_loop(e->mlx);
	}
	else
		write(2, "Error initializing mlx\n", 23);
	return (0);
}
