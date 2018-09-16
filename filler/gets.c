/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/25 04:35:11 by gbourgeo          #+#    #+#             */
/*   Updated: 2014/01/26 19:30:40 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int			get_info(t_board *board)
{
	char		*tmp;

	tmp = NULL;
	if (get_next_line(0, &tmp) < 1)
		return (-1);
	if (ft_strstr(tmp, "p1") != NULL)
	{
		board->my_id = ft_strdup("O");
		board->op_id = ft_strdup("X");
	}
	else
	{
		board->my_id = ft_strdup("X");
		board->op_id = ft_strdup("O");
	}
	ft_strclr(tmp);
	return (0);
}

int			get_board(t_board *board)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	if (get_next_line(0, &tmp) < 1)
		return (-1);
	board->map_x  = ft_atoi((tmp = ft_strchr(tmp, ' ') + 1));
	board->map_y  = ft_atoi((tmp = ft_strchr(tmp, ' ') + 1));
	if ((board->map = malloc(sizeof(char*) * (board->map_x + 1))) == NULL)
		return (-1);
	ft_strclr(tmp);
	if (get_next_line(0, &tmp) < 1)
		return (-1);
	ft_strclr(tmp);
	while (i < board->map_x && get_next_line(0, &tmp) > 0)
	{
		board->map[i++] = ft_strdup(tmp + 4);
		ft_strclr(tmp);
	}
	board->map[i] = '\0';
	return (0);
}

int			get_piece(t_piece *piece)
{
	char	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	if (get_next_line(0, &tmp) < 1)
		return (-1);
	piece->p_x = ft_atoi((tmp = ft_strchr(tmp, ' ') + 1));
	piece->p_y = ft_atoi((tmp = ft_strchr(tmp, ' ') + 1));
	ft_strclr(tmp);
	if ((piece->map = (char**)malloc(sizeof(char*) * (piece->p_x + 1))) == NULL)
		return (-1);
	while (i < piece->p_x && get_next_line(0, &tmp) > 0)
	{
		piece->map[i++] = ft_strdup(tmp);
		ft_strclr(tmp);
	}
	piece->map[i] = '\0';
	return (0);
}
