/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alcu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/09 16:05:02 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/03/10 06:15:37 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALCU_H
# define ALCU_H
# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# define PLAYER 1
# define COMPUT 2
# define EMPTY ' '

typedef struct	s_env
{
	int		x;
	int		y;
	char	**board;
}				t_env;

int				ft_param_error(int ac, char **av);
int				ft_check_param(char *s1, char *s2);
void			ft_play_game(t_env *e);
int				ft_player_shot(t_env *e);
int				ft_computer_shot(t_env *e);
int				check_buf(char *buf, int y);
int				ft_check_board(int first, int pos, t_env *e);
int				ft_check_for_a_winner(int turns, t_env *e);
void			ft_print_info(char **board, int player);
void			ft_print_board(char **board);

#endif
