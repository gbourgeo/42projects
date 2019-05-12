/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 04:54:35 by rfontain          #+#    #+#             */
/*   Updated: 2019/03/31 22:39:46 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "shell_term.h"

void	next_word(t_line *line)
{
	if (line->index == line->len)
		return ;
	while (line->index < line->len && line->curr->buff[line->index] != ' ')
		right_arrow(line);
	while (line->index < line->len && line->curr->buff[line->index] == ' ')
		right_arrow(line);
}

void	prev_word(t_line *line)
{
	if (line->index == 0)
		return ;
	while (line->index > 0 && line->curr->buff[line->index - 1] == ' ')
		left_arrow(line);
	while (line->index > 0 && line->curr->buff[line->index - 1] != ' ')
		left_arrow(line);
}
