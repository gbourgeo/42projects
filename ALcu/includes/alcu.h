/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alcu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/09 16:05:02 by gbourgeo          #+#    #+#             */
/*   Updated: 2019/08/02 22:42:11 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALCU_H
# define ALCU_H

# include <unistd.h>
# include <stdlib.h>
# include <termcap.h>
# include "libft.h"

# define PLAYER			0
# define COMPUT			1
# define EMPTY			' '
# define NUMBER_TO_WIN	4

typedef struct	s_env
{
	int		x;
	int		y;
	char	**board;
}				t_env;

int				ft_param_error(int ac, char **av);
int				ft_check_param(char *s1, char *s2);
void			ft_play_game(t_env *e);
int				ft_moves(t_env *e, int player);
int				ft_check_buf(char *buf, int y);
int				ft_check_board(int first, int pos, t_env *e);
int				ft_check_for_a_winner(int turns, t_env *e);
void			ft_print_board(t_env *e);

int				ft_tputs(char *str);
int				ft_tgetent(char *term);

#endif
