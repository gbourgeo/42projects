/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/29 20:12:44 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/09/16 23:11:35 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		ft_usage(char *name, t_env *e)
{
	int			i;

	i = 0;
	ft_putstr_fd("Usage: ", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd(" [name1] [name2]\nAvailable names :", 2);
	while (e->fract[i])
	{
		ft_putstr_fd("- ", 2);
		ft_putendl_fd(e->fract[i], 2);
		i++;
	}
}

static int		ft_get_fractal_name(char **av, t_env *e)
{
	int			i;

	i = 0;
	while (e->fract[i])
	{
		if (ft_strcmp(av[1], e->fract[i]) == 0)
			e->one.type = i;
		i++;
	}
	if (e->one.type == -1)
		return (1);
	if (av[2])
	{
		i = 0;
		while (e->fract[i])
		{
			if (ft_strcmp(av[2], e->fract[i]) == 0)
				e->two.type = i;
			i++;
		}
		if (e->two.type == -1)
			return (1);
	}
	return (0);
}

static void		init_img(t_img *i)
{
	i->type = -1;
	i->win = NULL;
	i->img = NULL;
	i->data = NULL;
	i->zoom = 1.0;
	i->r = 1;
	i->g = 12;
	i->b = 6;
}

int				main(int ac, char **av)
{
	t_env		e;
	static char	*fract[] = {FRACTAL_NAMES, 0};
	static void	(*draw[])(t_env *, t_img *) = {FRACTAL_FUNCT};

	e.fract = fract;
	e.draw = draw;
	e.mlx = NULL;
	init_img(&e.one);
	init_img(&e.two);
	e.local_endian = 0x11223344;
	e.local_endian = (((unsigned char *)&e.local_endian)[0] == 0x11) ? 1 : 0;
	if (ac > 1 && !ft_get_fractal_name(av, &e))
		ft_fractol(&e);
	ft_usage(av[0], &e);
	return (EXIT_FAILURE);
}
