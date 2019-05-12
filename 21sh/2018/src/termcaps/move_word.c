/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 04:54:35 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/25 23:11:15 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "shell_term.h"

static void	deal_erase_complet(t_line *line)
{
	size_t	index;

	index = line->index;
	go_end(line);
	tputs(tgetstr("sc", NULL), 1, ft_pchar);
	tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgetstr("cr", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	tputs(tgetstr("rc", NULL), 1, ft_pchar);
	*line->e_cmpl &= ~COMPLETION;
	line->index = index;
}

void		next_word(t_line *line)
{
	if (line->index == line->len)
		return ;
	if (*line->e_cmpl & COMPLETION)
		deal_erase_complet(line);
	tputs(tgetstr("vi", NULL), 1, ft_pchar);
	while (line->index < line->len && line->curr->buff[line->index] != ' ')
		right_arrow(line);
	while (line->index < line->len && line->curr->buff[line->index] == ' ')
		right_arrow(line);
	tputs(tgetstr("ve", NULL), 1, ft_pchar);
}

void		prev_word(t_line *line)
{
	if (line->index == 0)
		return ;
	if (*line->e_cmpl & COMPLETION)
		deal_erase_complet(line);
	tputs(tgetstr("vi", NULL), 1, ft_pchar);
	while (line->index > 0 && line->curr->buff[line->index - 1] == ' ')
		left_arrow(line);
	while (line->index > 0 && line->curr->buff[line->index - 1] != ' ')
		left_arrow(line);
	tputs(tgetstr("ve", NULL), 1, ft_pchar);
}
