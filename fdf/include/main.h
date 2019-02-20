/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/18 12:30:53 by gbourgeo          #+#    #+#             */
/*   Updated: 2018/12/15 07:16:53 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# include "libft.h"
# include <unistd.h>
# include <mlx.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

# define WIN_WIDTH 1400
# define WIN_HEIGTH 800
# define ECART_X e->ecart_x
# define ECART_Y e->ecart_y
# define ECART_RATE 2

# define CSTE e->cste
# define CSTE_VAL 1
# define CSTE_RATE 0.1

# define BCKGRD 0x000000
# define TOP 0xFFFFFF
# define MID 0x505050
# define GROUND 0x00F8F8

# define ESC 53
# define MINUS 78
# define PLUS 69
# define DIV 75
# define MULT 67

# define K_UP 126
# define K_D 125
# define K_LE 123
# define K_RI 124
# define MOVE_RATE 100

# define K_ONE 83
# define K_TWO 84
# define K_THREE 85
# define K_FIVE 87

# define PLUS_1 e->i + 1 < e->coord->len
# define NEXT e->coord->next && e->i < e->coord->next->len
# define NEXT_PLUS(size) e->i + size < e->coord->next->len
# define PREV e->coord->prev && e->i < e->coord->prev->len
# define PREV_PREV e->coord->prev->prev && e->i < e->coord->prev->prev->len
# define OLD_X1(p) (p->old_x1 % ECART_X || (e->i > 0 && e->coord->z[e->i - 1]))
# define OLD_X(p) (p->old_x % ECART_X || (PREV && e->coord->prev->z[e->i]))
# define X1 e->coord->z[e->i + 1]
# define X2 (p->x2 % ECART_X || (e->i + 1 < e->coord->len && X1 ))
# define FIND_X(point) point->x - point->x % ECART_X
# define FIND_Y(point) point->y - point->y % ECART_Y
# define Z1_Z2(diff) e->coord->z[e->i] diff e->coord->z[e->i + 1]
# define Z1_Z3(diff) e->coord->z[e->i] diff e->coord->next->z[e->i]
# define Z3_Z4(diff) e->coord->next->z[e->i] diff e->coord->next->z[e->i + 1]
# define Z2_Z4(diff) e->coord->z[e->i + 1] diff e->coord->next->z[e->i + 1]
# define Z1_OLDZ1(diff) e->coord->z[e->i] diff e->coord->z[e->i - 1]
# define NO_FLOAT_X1 (p->x - p->old_x1) / (p->x1 - p->old_x1)
# define NO_FLOAT_Y1 (p->y - p->old_y) / (p->y1 - p->old_y)
# define VAL_NEXT_Z_PLUS_X(nb, sign) e->coord->next->z[e->i + nb] sign 0

typedef struct		s_map
{
	char			*line;
	struct s_map	*next;
}					t_map;

typedef struct		s_coord
{
	int				len;
	int				*z;
	struct s_coord	*next;
	struct s_coord	*prev;
}					t_coord;

typedef struct		s_img
{
	void			*ptr;
	char			*data;
	int				w;
	int				h;
	int				drawn;
}					t_img;

enum				e_list
{
	parallel,
	conic,
	isometric
};

typedef struct		s_env
{
	int				i;
	void			*mlx;
	void			*win;
	t_coord			*coord;
	int				map_w;
	int				map_h;
	t_img			img;
	int				proj;
	int				bpp;
	int				sizeline;
	int				local_endian;
	int				endian;
	int				ground;
	int				top;
	int				mid;
	int				bckgrd;
	int				ecart_x;
	int				ecart_y;
	int				img_x;
	int				img_y;
	float			cste;
}					t_env;

typedef struct		s_point
{
	int		x;
	int		y;
	int		x1;
	int		y1;
	int		x2;
	int		y2;
	int		x3;
	int		y3;
	int		img_w;
	int		img_h;
	int		ratio;
}					t_point;

t_map				*get_map(const char *av);
int					get_next_line(int const fd, char **line);
void				ft_free_map(t_map **map);
void				ft_free_all(t_env *e);
t_coord				*get_coord(t_map *map, t_env *e, t_coord *prev);
char				**ft_strangesplit(char const *s);
void				fdf(t_env *e);
void				draw(t_env *e);
void				draw_parallel(t_env *e);
void				draw_isometric(t_env *e);
void				draw_conic(t_env *e);
void				ft_directional_move(int keycode, t_env *e);
void				ft_projection_type(int keycode, t_env *e);
void				ft_resize_image(int keycode, t_env *e);
void				ft_change_constante(int keycode, t_env *e);
int					ft_abs(int diff);
int					ft_pow(int nb, int power);
int					ft_calc_diagonal(t_point *p, t_env *e, int c);
int					ft_calc_diagonal_negative(t_point *p, t_env *e, int c);
int					ft_calc_diagonal_negative_plus(t_point *p, t_env *e, int c);
int					ft_pre_calc_diagonal_negative(t_point *p, t_env *e, int c);
void				ft_put_color(t_env *e, t_point *point, int color);
void				init_point(t_env *e, t_point *point);
void				calc_init_point(t_env *e, t_point *point);
void				calc_init_point_next_next(t_env *e, t_point *p);
void				ft_clear_image(t_env *e);
void				ft_end(char *str, t_env *e);
void				ft_draw_case_one(t_env *e, t_point *p, char next);
void				ft_draw_case_two(t_env *e, t_point *p, char next);
void				ft_draw_case_three(t_env *e, t_point *p, char next);
void				ft_draw_case_four(t_env *e, t_point *p, char next);

#endif
