/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beborch <beborch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 19:46:44 by beborch           #+#    #+#             */
/*   Updated: 2018/09/06 13:20:32 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void		print_map(char map[MAX][MAX], size_t map_size)
{
	t_size_t2	i;

	i.y = 0;
	while (i.y < map_size)
	{
		i.x = 0;
		while (i.x < map_size)
		{
			write(1, &map[i.y][i.x], 1);
			i.x++;
		}
		write(1, "\n", 1);
		i.y++;
	}
}

static int		error(void)
{
	write(1, "error\n", 6);
	return (1);
}

static int		usage(const char *av)
{
	ft_putstr_fd("Usage:\n\t", 2);
	ft_putstr_fd(av, 2);
	ft_putendl_fd(" [file]", 2);
	return (1);
}

int				main(int argc, char *argv[])
{
	t_fill		fill;

	if (argc != 2)
		return (usage(argv[0]));
	if ((fill.file = open(argv[1], O_RDONLY)) < 0)
		return (error());
	if ((fill.ret = read(fill.file, fill.buff, BUFF_SIZE)) < 0)
		return (error());
	fill.buff[fill.ret] = '\0';
	if (fill.ret < PIECE_SIZE - 1 || fill.ret > MAX_PIECES * PIECE_SIZE)
		return (error());
	if (check_integrity(&fill))
		return (error());
	if (parse(&fill) == -1)
		return (error());
	if (check_parse(&fill) == -1)
		return (error());
	solver(&fill);
	print_map(fill.map, fill.map_size);
}
