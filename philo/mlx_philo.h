/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_philo.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/11 19:24:43 by ppellegr          #+#    #+#             */
/*   Updated: 2014/05/11 19:24:46 by ppellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_PHILO_H
# define MLX_PHILO_H
# include <unistd.h>
# include <stdlib.h>
# include <mlx.h>
# include "philo.h"
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# define WIN_X			640
# define WIN_Y			480
# define COL(R, G, B)	((B) | ((G) << 8) | ((R) << 16))
# define GETB(C)		((C) << 24 >> 24 & 255)
# define GETR(C)		((C) >> 16)
# define GETG(C)		(((C) - (GETR((C)) << 16)) >> 8)

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	int				win_x;
	int				win_y;
	void			*img;
	struct s_div	*divs;
}					t_env;

/*
** mlx.c
*/

void				init_mlx(t_env *e);
int					key_hook(int keycode);
int					expose_hook(t_env *e);
void				*mlx(void *divs);
int					draw(t_env *e);

#endif
