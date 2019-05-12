/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 05:18:39 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/29 21:56:34 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "shell_term.h"

static void	expand_select_left(t_line *line, int diff, int mal)
{
	if (mal == 2)
	{
		line->slct_end = (int)line->index + 1;
		diff = line->slct_end;
	}
	line->slct_beg = diff > 0 ? diff - mal : 0;
	line->index = (size_t)line->slct_beg;
	tputs(tgetstr("mr", NULL), 1, ft_pchar);
	ft_putchar_fd(line->curr->buff[line->index + 1], 0);
	tputs(tgetstr("me", NULL), 1, ft_pchar);
	if (line->index
			&& (line->index + line->lprompt) % line->nb_col == line->nb_col - 1)
		deal_scroll(line, 1, 1);
	tputs(tgoto(tgetstr("ch", NULL), 0,
				(line->lprompt + line->index) % line->nb_col), 1, ft_pchar);
}

static void	is_in_completion(t_line *line)
{
	int		index_tmp;

	index_tmp = line->index;
	if (*line->e_cmpl & COMPLETION)
	{
		tputs(tgetstr("sc", NULL), 1, ft_pchar);
		go_end(line);
		tputs(tgetstr("do", NULL), 1, ft_pchar);
		tputs(tgetstr("cr", NULL), 1, ft_pchar);
		tputs(tgetstr("cd", NULL), 1, ft_pchar);
		tputs(tgetstr("rc", NULL), 1, ft_pchar);
		line->index = index_tmp;
		*line->e_cmpl &= ~COMPLETION;
		free(line->curr->buff_tmp);
		line->curr->buff_tmp = NULL;
	}
}

void		select_left(t_line *line)
{
	if (line->index == 0)
		return ;
	is_in_completion(line);
	if (line->slct_beg < 0)
		expand_select_left(line, line->slct_end, 2);
	else
	{
		if (line->slct_beg == (int)line->index)
			expand_select_left(line, line->slct_beg, 1);
		else
		{
			ft_putchar_fd(line->curr->buff[line->index], 0);
			line->slct_end -= 1;
			line->index -= 1;
			if (line->index
					&& (line->index + line->lprompt) % line->nb_col
					== line->nb_col - 1)
				deal_scroll(line, 1, 1);
			tputs(tgoto(tgetstr("ch", NULL), 0,
						(line->lprompt + line->index) % line->nb_col), 1,
					ft_pchar);
		}
	}
}

static void	expand_select_right(t_line *line, int diff)
{
	line->slct_end = diff < (int)line->len ? diff + 1 : (int)line->len;
	line->index = (size_t)line->slct_end;
	tputs(tgetstr("mr", NULL), 1, ft_pchar);
	ft_putchar_fd(line->curr->buff[line->index - 1], 0);
	tputs(tgetstr("me", NULL), 1, ft_pchar);
	if (line->index && (line->index + line->lprompt) % line->nb_col == 0)
		deal_scroll(line, 0, line->nb_line);
	tputs(tgoto(tgetstr("ch", NULL), 0,
				(line->lprompt + line->index) % line->nb_col), 1, ft_pchar);
}

void		select_right(t_line *line)
{
	if (line->index == line->len)
		return ;
	if (line->slct_beg < 0)
	{
		line->slct_beg = (int)line->index;
		expand_select_right(line, line->slct_beg);
	}
	else
	{
		if (line->slct_end == (int)line->index)
			expand_select_right(line, line->slct_end);
		else
		{
			ft_putchar_fd(line->curr->buff[line->index], 0);
			line->slct_beg += 1;
			line->index += 1;
			if (line->index && (line->index + line->lprompt) % line->nb_col
					== 0)
				deal_scroll(line, 0, line->nb_line);
			tputs(tgoto(tgetstr("ch", NULL), 0,
						(line->lprompt + line->index) % line->nb_col), 1,
					ft_pchar);
		}
	}
}
