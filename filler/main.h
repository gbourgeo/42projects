/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/21 21:07:38 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/01/26 19:52:23 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include "libft.h"
# define X_IN_MAP piece->c_x < 0 || piece->c_x > board->map_x
# define Y_IN_MAP piece->c_y < 0 || piece->c_y > board->map_y

typedef struct	s_board
{
	char	*my_id;
	char	*op_id;
	int		map_x;
	int		map_y;
	char	**map;
}				t_board;

typedef struct	s_piece
{
	int		p_x;
	int		p_y;
	int		s_x;
	int		s_y;
	int		t_x;
	int		t_y;
	int		c_x;
	int		c_y;
	char	**map;
}				t_piece;

int			get_next_line(int const fd, char **line);
int			get_info(t_board *board);
int			get_board(t_board *board);
int			get_piece(t_piece *piece);
int			ft_start_program(t_board *board, t_piece *piece);
void		init_my_pos(t_piece *piece);

#endif
