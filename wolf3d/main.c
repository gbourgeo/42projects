/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/24 17:00:32 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/27 12:09:23 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int		ft_err(char *mess, t_env *e)
{
	int			i;

	i = 0;
	if (e->map)
	{
		while (e->map[i])
			free(e->map[i++]);
		free(e->map[i]);
		free(e->map);
	}
	ft_putendl_fd(mess, 2);
	return (1);
}

static int		ft_check_map(t_env *e)
{
	int			i;
	int			j;

	i = 0;
	while (e->map[i])
	{
		if (i == 0 || !e->map[i + 1])
		{
			j = 0;
			while (e->map[i][j] && e->map[i][j] == '1')
				j++;
			if (e->map[i][j])
				return (ft_err("\nMap border not limited (!= 1)", e));
		}
		else if (e->map[i][0] != '1' ||
				e->map[i][ft_strlen(e->map[i]) - 1] != '1')
			return (ft_err("\nMap border not limited (!= 1)", e));
		i++;
	}
	return (0);
}

static int		ft_check_player(t_env *e)
{
	int			i;
	char		*tmp;

	i = 0;
	while (e->map[i])
	{
		if ((tmp = ft_strchr(e->map[i], 'X')) ||
			(tmp = ft_strchr(e->map[i], '*')))
		{
			*tmp = '0';
			e->player.pos_x = i + 0.0;
			e->player.pos_y = ft_strlen(e->map[i]) - ft_strlen(tmp) + 0.0;
			e->player.dir_x = DIR_X;
			e->player.dir_y = DIR_Y;
			e->player.speed_move = SPEED_MOVE;
			e->player.speed_rotate = SPEED_ROTATE;
			return (0);
		}
		i++;
	}
	ft_putendl_fd("\nPlayer icon is missing on your map: 'X' or '*'", 2);
	return (1);
}

static void		ft_init_env(t_env *e)
{
	e->mlx = NULL;
	e->win = NULL;
	e->img = NULL;
	e->local_endian = 0x11223344;
	e->local_endian = (((unsigned char *)&e->local_endian)[0] == 0x11) ? 1 : 0;
	e->north = mlx_get_color_value(e->mlx, BLUE);
	e->south = mlx_get_color_value(e->mlx, PURPLE);
	e->east = mlx_get_color_value(e->mlx, RED);
	e->west = mlx_get_color_value(e->mlx, YELLOW);
	e->sky = mlx_get_color_value(e->mlx, CYAN);
	e->ground = mlx_get_color_value(e->mlx, GREEN);
	e->keys = K_NONE;
	e->cam.plane_x = CAM_X;
	e->cam.plane_y = CAM_Y;
}

int				main(int ac, char **av)
{
	t_env		e;

	(void)ac;
	e.map_h = 0;
	e.map_w = 0;
	e.map = get_map(av[1], &e);
	if (e.map == NULL)
		return (EXIT_FAILURE);
	if (ft_check_map(&e) || ft_check_player(&e))
		return (EXIT_FAILURE);
	ft_init_env(&e);
	ft_wolf(&e);
	ft_free_all(&e);
	ft_putendl("Bye.");
	return (EXIT_SUCCESS);
}
