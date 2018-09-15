/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beborch <beborch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/27 19:46:44 by beborch           #+#    #+#             */
/*   Updated: 2018/05/01 18:00:23 by beborch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void	set_zero_parse(t_fill *fill, int i)
{
	if (i == 0)
	{
		fill->i = 0;
		fill->j = 0;
		fill->num_piece = 0;
		fill->l = 0;
		i++;
	}
	else if (i == 1)
	{
		fill->num_piece++;
		fill->j = 0;
		fill->l = 0;
	}
	else
	{
		fill->parsing[fill->num_piece][fill->l] = fill->buff[fill->i];
		fill->parsing[fill->num_piece][fill->l + 1] = '\0';
		fill->i++;
		fill->l++;
	}
}

int			parse(t_fill *fill)
{
	set_zero_parse(fill, 0);
	while (fill->buff[fill->i] != '\0')
	{
		if (fill->buff[0] != '.' && fill->buff[0] != '#')
			return (-1);
		while (fill->buff[fill->i] == '\n')
		{
			fill->i++;
			fill->j++;
		}
		if (fill->j == 5)
		{
			fill->parsing[fill->num_piece][fill->l] = '\0';
			set_zero_parse(fill, 1);
		}
		else if (fill->j > 5)
			return (-1);
		while (fill->buff[fill->i] != '\n' && fill->buff[fill->i] != '\0')
			set_zero_parse(fill, 2);
	}
	fill->parsing[fill->num_piece + 1][0] = '\0';
	return (0);
}

void		ccpy(t_fill *fill, char *tmp)
{
	int i;

	i = 0;
	while (tmp[i] != '\0')
	{
		fill->parsing[fill->l][i] = tmp[i];
		i++;
	}
}

static void	set_zero_check(t_fill *fill, int i)
{
	fill->i = 0;
	fill->j = 0;
	fill->k = 0;
	if (i == 0)
	{
		i = 1;
		fill->l = 0;
		fill->tmp = 0;
	}
	else
		fill->l++;
}

int			check_parse(t_fill *fill)
{
	set_zero_check(fill, 0);
	while (fill->l < MAX_PIECES && fill->parsing[fill->l][0] != '\0')
	{
		while ((fill->i != 16) && fill->parsing[fill->l][fill->i] != '\0')
		{
			while (fill->parsing[fill->l][fill->i] == '.')
				fill->i++;
			while (g_pieces[fill->j][fill->k] == '.')
				fill->k++;
			while (fill->parsing[fill->l][fill->i] != '\0' &&
				(fill->parsing[fill->l][fill->i] == g_pieces[fill->j][fill->k]))
				increment(fill, 0);
			if (fill->parsing[fill->l][fill->i] != '\0')
				increment(fill, 1);
			if (fill->j == 19)
				return (-1);
		}
		if (fill->i != 16)
			return (-1);
		ccpy(fill, (char *)g_pieces[fill->j]);
		set_zero_check(fill, 1);
	}
	return (1);
}
