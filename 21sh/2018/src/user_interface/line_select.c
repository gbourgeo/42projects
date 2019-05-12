/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_selection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 18:26:18 by rfontain          #+#    #+#             */
/*   Updated: 2019/01/30 18:28:41 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	select_up(t_line *line)
{
	int		nb_col;

	nb_col = line->nb_col;
	while (nb_col--)
		select_left(line);
}

void	select_down(t_line *line)
{
	int		nb_col;

	nb_col = line->nb_col;
	while (nb_col--)
		select_right(line);
}
