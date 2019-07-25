/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/11 19:24:23 by ppellegr          #+#    #+#             */
/*   Updated: 2014/05/11 19:24:27 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "mlx_philo.h"
#include "stdio.h"

void	init_mlx(t_env *e)
{
	e->win_x = WIN_X;
	e->win_y = WIN_Y;
	e->mlx = mlx_init();
}

void	ft_state(t_env *e)
{
	t_philo			*tmp;
	int				i;
	int				x;
	t_outp			outp;

	i = 0;
	x = 50;
	while (i < 7)
	{
		tmp = &e->divs->philo[i];
		if (tmp->state == REST)
			outp.state = "RESTING";
		else if (tmp->state == THINK)
			outp.state = "THINKING";
		else if (tmp->state == EAT)
			outp.state = "EATING";
		else if (tmp->state == WAIT)
			outp.state = "WAITING";
		outp.life = ft_itoa(tmp->life);
		outp.philo = ft_strjoin("PHILOSOPHE ", ft_itoa(tmp->i++));
		mlx_string_put(e->mlx, e->win, x, 90, 0xE64848, outp.life);
		mlx_string_put(e->mlx, e->win, x, 70, 0xE64848, outp.state);
		mlx_string_put(e->mlx, e->win, x, 50, 0xE64848, outp.philo);
		x += 80;
	}
}

int		draw(t_env *e)
{
	usleep(300);
	mlx_clear_window(e->mlx, e->win);
	ft_state(e);
	return (0);
}

int		key_hook(int keycode)
{
	if (keycode == 65307)
		exit(0);
	return (0);
}

int		expose_hook(t_env *e)
{
	draw(e);
	return (0);
}
