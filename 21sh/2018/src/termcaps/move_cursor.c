/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 04:13:27 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/25 23:17:22 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell_term.h"
#include "put.h"
#include "shell.h"

void	go_home(t_line *line)
{
	tputs(tgetstr("vi", NULL), 1, ft_pchar);
	while ((int)line->index + (int)line->lprompt - (int)line->nb_col >= 0)
	{
		line->index -= line->nb_col;
		deal_scroll(line, 1, 1);
	}
	tputs(tgoto(tgetstr("ch", NULL), 0, line->lprompt), 1, ft_pchar);
	line->index = 0;
	tputs(tgetstr("ve", NULL), 1, ft_pchar);
}

void	deal_home(t_line *line)
{
	if (*line->e_cmpl & COMPLETION)
	{
		go_end(line);
		tputs(tgetstr("sc", NULL), 1, ft_pchar);
		tputs(tgetstr("do", NULL), 1, ft_pchar);
		tputs(tgetstr("cr", NULL), 1, ft_pchar);
		tputs(tgetstr("cd", NULL), 1, ft_pchar);
		tputs(tgetstr("rc", NULL), 1, ft_pchar);
		*line->e_cmpl &= ~COMPLETION;
	}
	go_home(line);
}

void	go_end(t_line *line)
{
	if (line->index == line->len)
		return ;
	tputs(tgetstr("vi", NULL), 1, ft_pchar);
	while (line->index + line->nb_col <= line->len)
	{
		line->index += line->nb_col;
		deal_scroll(line, 0, (int)line->nb_line);
	}
	if ((line->len + line->lprompt) % line->nb_col == 0
			|| (line->index + line->lprompt) % line->nb_col
				> (line->len + line->lprompt) % line->nb_col)
		tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0,
				(line->len + line->lprompt) % line->nb_col), 1, ft_pchar);
	line->index = line->len;
	tputs(tgetstr("ve", NULL), 1, ft_pchar);
}

void	left_arrow(t_line *line)
{
	if (*line->e_cmpl & COMPLETION && line->is_putb)
	{
		line->key = LEFT;
		get_complet(line);
		return ;
	}
	if (line->curr->buff_tmp)
	{
		free(line->curr->buff_tmp);
		line->curr->buff_tmp = NULL;
		while (line->hist->prev)
			line->hist = line->hist->prev;
	}
	if (line->index > 0)
		line->index -= 1;
	else
		write(2, "\a", 1);
	if (line->index
			&& (line->index + line->lprompt) % line->nb_col == line->nb_col - 1)
		deal_scroll(line, 1, 1);
	tputs(tgoto(tgetstr("ch", NULL), 0,
				(line->index + line->lprompt) % line->nb_col), 1, ft_pchar);
}

void	right_arrow(t_line *line)
{
	if (*line->e_cmpl & COMPLETION && line->is_putb)
	{
		line->key = RIGHT;
		get_complet(line);
		return ;
	}
	if (line->curr->buff_tmp)
	{
		free(line->curr->buff_tmp);
		line->curr->buff_tmp = NULL;
		while (line->hist->prev)
			line->hist = line->hist->prev;
	}
	if (line->index == line->len)
	{
		ft_putchar_fd('\a', 2);
		return ;
	}
	line->index += 1;
	if (line->index && (line->index + line->lprompt) % line->nb_col == 0)
		deal_scroll(line, 0, (int)line->nb_line);
	tputs(tgoto(tgetstr("ch", NULL), 0,
				(line->index + line->lprompt) % line->nb_col), 1, ft_pchar);
}
