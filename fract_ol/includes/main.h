/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/29 20:19:43 by gbourgeo          #+#    #+#             */
/*   Updated: 2016/05/19 20:21:36 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "libft.h"
# include <mlx.h>
# include <math.h>

# define NAME "Fract'ol - gbourgeo"

# define WIN_W 800
# define WIN_H 600

# define ESC 53

# define KB_UP 126
# define KB_DOWN 125
# define KB_LEFT 123
# define KB_RIGHT 124

# define KB_1 83
# define KB_2 84
# define KB_3 85
# define KB_4 86

# define KB_HOME 115
# define KB_END 119
# define KB_FN 279
# define KB_DEL 117
# define KB_PUP 116
# define KB_PDO 121

# define M_WHEEL_UP 4
# define M_WHEEL_DOWN 5

# define ITERATION_MAX 150
# define FRACTAL_NAMES "julia", "brain", "mandelbrot", "ship"
# define FRACTAL_FUNCT ft_julia, ft_brain, ft_mandel, ft_ship
# define ZOOM 0.25
# define MOVE 50
# define RATIO 2
# define SCALE_X ((p.x + i->x) / i->zoom)
# define SCALE_Y ((p.y + i->y) / i->zoom)

typedef struct		s_point
{
	int				x;
	int				y;
	double			cr;
	double			ci;
	double			zr;
	double			zi;
	size_t			i;
	double			tmp;
}					t_point;

typedef struct		s_img
{
	int				x;
	int				y;
	int				type;
	void			*win;
	void			*img;
	char			*data;
	double			zoom;
	double			rc;
	double			ic;
	double			min_x;
	double			max_x;
	double			min_y;
	double			max_y;
	int				r;
	int				g;
	int				b;
}					t_img;

typedef struct		s_env
{
	char			**fract;
	void			(**draw)(struct s_env *, t_img *);
	void			*mlx;
	t_img			one;
	t_img			two;
	int				bpp;
	int				sline;
	int				endian;
	int				local_endian;
}					t_env;

void				ft_put_color(t_env *e, t_point *p, t_img *i);
void				ft_change_color(t_env *e, t_img *i, int keycode, int win);
char				*ft_strtolower(char *str);
void				ft_fractol(t_env *e);
int					key_one_hook(int keycode, t_env *e);
int					mouse_one_hook(int keycode, int x, int y, t_env *e);
int					expose_one_hook(t_env *e);
int					one_hook(int x, int y, t_env *e);
void				do_one_draw(t_env *e, int type, int movex, int movey);
int					key_two_hook(int keycode, t_env *e);
int					mouse_two_hook(int keycode, int x, int y, t_env *e);
int					expose_two_hook(t_env *e);
int					two_hook(int x, int y, t_env *e);
void				do_two_draw(t_env *e, int type, int movex, int movey);
void				ft_end(char *str, t_env *e, char win, int status);
void				ft_mandel(t_env *e, t_img *i);
void				ft_julia(t_env *e, t_img *i);
void				ft_ship(t_env *e, t_img *i);
void				ft_brain(t_env *e, t_img *i);

#endif
