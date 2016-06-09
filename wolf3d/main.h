/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/18 12:30:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/27 10:22:08 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include "libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <mlx.h>
# include <math.h>

/*
** fcntl: open, stdio: perror, unistd: close
*/

# define WIN_WIDTH 1024
# define WIN_HEIGTH 580

# define ESC 53
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124

# define CYAN (0x00FFFF)
# define BLUE (0x0000FF)
# define GREEN (0x00FF00)
# define RED (0xFF0000)
# define PURPLE (0xFF00FF)
# define YELLOW (0xFFFF00)

# define DIR_X (-1)
# define DIR_Y (0)
# define CAM_X (0)
# define CAM_Y (0.66)
# define SPEED_MOVE (0.15)
# define SPEED_ROTATE (0.05)

# define KEYPRESS (2)
# define KEYPRESSMASK (1L<<0)
# define KEYRELEASE (3)
# define KEYRELEASEMASK (1L<<1)

typedef enum		e_key
{
	K_NONE = 0x0,
	K_ESC = 0x1,
	K_UP = 0x2,
	K_DOWN = 0x4,
	K_LEFT = 0x8,
	K_RIGHT = 0x10
}					t_key;

typedef struct		s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			speed_move;
	double			speed_rotate;
}					t_player;

typedef struct		s_cam
{
	double			x;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			dist_wall;
}					t_cam;

typedef struct		s_draw
{
	int				x;
	int				map_x;
	int				map_y;
	int				height;
	int				start;
	int				end;
	int				color;
	int				side;
	int				hit;
	int				step_x;
	int				step_y;
	double			dist_side_x;
	double			dist_side_y;
	double			dist_delta_x;
	double			dist_delta_y;
}					t_draw;

typedef struct		s_env
{
	char			**map;
	int				map_w;
	int				map_h;
	void			*mlx;
	void			*win;
	void			*img;
	char			*data;
	int				local_endian;
	int				endian;
	int				bpp;
	int				sizeline;
	int				north;
	int				south;
	int				east;
	int				west;
	int				sky;
	int				ground;
	t_cam			cam;
	t_key			keys;
	t_draw			draw;
	t_player		player;
}					t_env;

typedef void		(t_fkey) (t_env *e);

typedef struct		s_keys
{
	int				code;
	t_key			flag;
	t_fkey			*callback;
}					t_keys;

char				**get_map(char *av, t_env *e);
void				ft_free_all(t_env *e);
void				ft_wolf(t_env *e);
void				ft_end(char *str, t_env *e, int status);
void				draw(t_env *e);
void				ft_raycast(t_env *e);
void				move(t_env *e);

#endif
