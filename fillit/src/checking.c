/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beborch <beborch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/29 02:36:29 by beborch           #+#    #+#             */
/*   Updated: 2018/09/06 13:28:06 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static int		check_piece(const char *tetri, int i)
{
	int			piece;

	i = 0;
	piece = 0;
	while (tetri[i] && i < 20)
	{
		if ((i + 1) % 5 == 0)
		{
			if (tetri[i] != '\n')
				return (0);
		}
		else if (tetri[i] != '.' && tetri[i] != '#')
			return (0);
		else if (tetri[i] == '#')
		{
			if ((i < 5 || tetri[i - 5] != '#') &&
				((i + 2) % 5 == 0 || tetri[i + 1] != '#') &&
				(i >= 15 || tetri[i + 5] != '#') &&
				(i % 5 == 0 || tetri[i - 1] != '#'))
				return (0);
			piece++;
		}
		i++;
	}
	return (i == 20 && piece == 4 && (tetri[i] == '\n' || !tetri[i]));
}

int				check_integrity(t_fill *fill)
{
	int			i;

	i = 0;
	while (fill->buff[i] != '\0' && i < fill->ret)
	{
		if (fill->buff[i] == '\n')
		{
			if (fill->buff[i + 1] == '\n')
				return (1);
			i++;
		}
		else if (!check_piece(fill->buff + i, 0))
			return (1);
		else
			i += 21;
	}
	return (i == fill->ret);
}
