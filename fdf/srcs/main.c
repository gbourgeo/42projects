/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/18 12:15:14 by gbourgeo          #+#    #+#             */
/*   Updated: 2015/03/21 04:30:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		ft_baseconvert(char *str)
{
	int		i;
	int		j;
	int		color;

	i = 0;
	j = 5;
	color = 0;
	while (str[i++])
		str[i - 1] = ft_tolower(str[i - 1]);
	i = 0;
	if (str[0] == '0' && str[1] == 'x')
		i = 2;
	while (j >= 0)
	{
		if (str[i] && str[i] >= 'a' && str[i] <= 'f')
			color += (int)((str[i] - 87) * ft_pow(16, j));
		else if (str[i] && str[i] >= 'A' && str[i] <= 'F')
			color += (int)((str[i] - 55) * ft_pow(16, j));
		else if (str[i] && str[i] >= '0' && str[i] <= '9')
			color += (int)((str[i] - 48) * ft_pow(16, j));
		if (str[i])
			i++;
		j--;
	}
	return (color);
}

static void		ft_init_env(t_env *e, char **av)
{
	e->mlx = NULL;
	e->win = NULL;
	e->coord = NULL;
	e->map_w = 0;
	e->map_h = 0;
	e->proj = parallel;
	e->local_endian = 0x11223344;
	e->local_endian = (((unsigned char *)&e->local_endian)[0] == 0x11) ? 1 : 0;
	e->ground = av[2] ? ft_baseconvert(av[2]) : GROUND;
	e->top = (av[2] && av[3]) ? ft_baseconvert(av[3]) : TOP;
	e->mid = (av[2] && av[3] && av[4]) ? ft_baseconvert(av[4]) : MID;
	e->ecart_x = 1;
	e->ecart_y = 1;
	e->img_x = 0;
	e->img_y = 0;
	e->cste = CSTE_VAL;
}

static void		ft_usage(void)
{
	ft_putendl("usage: ./fdf file [ground color] [top color] [mid_color]");
	ft_putstr("usage: All colors are optionnal and must be in hexadecimal, ");
	ft_putendl(" begining with 0x or not.");
	ft_putstr("usage: By default, [ground] = 0x00F8F8");
	ft_putstr(", [top] = 0xFFFFFFF");
	ft_putendl(", [mid] = 0x505050");
}

int				main(int ac, char **av)
{
	t_env		e;
	t_map		*map;

	if (ac < 2 || ac > 5)
		ft_usage();
	else if ((map = get_map(av[1])))
	{
		ft_init_env(&e, av);
		ft_putendl("Getting your maps' coordonates...");
		if ((e.coord = get_coord(map, &e, NULL)))
		{
			ft_free_map(&map);
			fdf(&e);
			ft_free_all(&e);
		}
	}
	return (EXIT_FAILURE);
}
