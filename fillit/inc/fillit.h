/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beborch <beborch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 20:01:47 by beborch           #+#    #+#             */
/*   Updated: 2018/09/05 02:11:59 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# define BUFF_SIZE (1024)
# define PIECES (19)
# define MAX_PIECES (26)
# define PIECE_SIZE (21)
# define MAX (50)

# include "libft.h"
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct		s_size_t2
{
	size_t			x;
	size_t			y;
}					t_size_t2;

typedef struct		s_fill
{
	int				i;
	int				j;
	int				k;
	int				l;
	int				tmp;
	char			parsing[MAX_PIECES][17];
	int				file;
	int				ret;
	char			buff[BUFF_SIZE];
	size_t			num_piece;
	size_t			map_size;
	size_t			piece;
	char			map[MAX][MAX];
	t_size_t2		coord[MAX_PIECES];
}					t_fill;

static const char	*g_pieces[PIECES] =
{
	"#...#...#...#...",
	"####............",
	"#...#...##......",
	".#...#..##......",
	"###.#...........",
	"###...#.........",
	"#...###.........",
	"..#.###.........",
	"##..#...#.......",
	"##...#...#......",
	"##..##..........",
	"###..#..........",
	".#..###.........",
	"#...##..#.......",
	".#..##...#......",
	"#...##...#......",
	".#..##..#.......",
	"##...##.........",
	".##.##.........."
};

void				solver(t_fill *fill);
void				init_map(size_t map_size, char map[MAX][MAX]);
int					check_parse(t_fill *fill);
int					parse(t_fill *fill);
void				place(char *piece, t_size_t2 *pos, char map[MAX][MAX],
		char letter);
void				increment(t_fill *fill, int i);
int					check_integrity(t_fill *fill);

#endif
