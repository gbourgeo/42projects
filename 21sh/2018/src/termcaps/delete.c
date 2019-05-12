/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 04:51:36 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/29 21:55:26 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "shell_term.h"

static void	del_left_tool(t_line *line)
{
	if ((line->index + line->lprompt) % line->nb_col == line->nb_col - 1
			&& line->index == line->len)
	{
		tputs(tgetstr("sc", NULL), 1, ft_pchar);
		ft_putchar_fd(' ', 0);
		tputs(tgetstr("rc", NULL), 1, ft_pchar);
	}
	if (line->len + line->lprompt > line->nb_col - 1)
		del_lines(line);
}

static void	del_left(t_line *line)
{
	line->len = ft_strlen(line->curr->buff);
	if (line->index && (line->index + line->lprompt) % line->nb_col == 0)
		tputs(tgetstr("up", NULL), 1, ft_pchar);
	if (line->index != 0)
	{
		if (line->index > 0 && line->curr->buff[line->index - 1] == '/')
			line->tree[2] = free_tree(line->tree[2]);
		line->index = line->index > 0 ? line->index - 1 : 0;
		ft_strcpy(&line->curr->buff[line->index],
				&line->curr->buff[line->index + 1]);
		line->len = line->len > 0 ? line->len - 1 : 0;
		tputs(tgoto(tgetstr("ch", NULL), 0,
					(line->index + line->lprompt) % line->nb_col), 1, ft_pchar);
		tputs(tgetstr("dc", NULL), 1, ft_pchar);
	}
	else
		write(2, "\a", 1);
	del_left_tool(line);
}

void		deal_dleft(t_line *line)
{
	if (*(line->e_cmpl) & COMPLETION)
	{
		delete_down();
		*(line->e_cmpl) &= ~COMPLETION;
		free(line->curr->buff_tmp);
		line->curr->buff_tmp = NULL;
		line->index = line->len;
	}
	else
		del_left(line);
}

void		del_right(t_line *line)
{
	int		j;

	if (*(line->e_cmpl) & COMPLETION)
		line->tmp[0] = 10;
	else
	{
		if (line->index == line->len)
			write(2, "\a", 1);
		j = -1;
		if (line->curr->buff[line->index] == '/')
			line->tree[2] = free_tree(line->tree[2]);
		while (line->index + ++j < line->len)
			line->curr->buff[line->index + j] =
				line->curr->buff[line->index + j + 1];
		line->len = line->len > line->index ? line->len - 1 : line->index;
		del_lines(line);
	}
}
