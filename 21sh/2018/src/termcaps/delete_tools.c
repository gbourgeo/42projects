/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 23:14:29 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/29 13:59:47 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "shell_term.h"

static void	get_to_left(t_line *line)
{
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

static void	deal_beg_line(t_line *line, int pos)
{
	size_t	index;

	if (pos != 1)
		tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0,
				(line->index + line->lprompt) % line->nb_col), 1, ft_pchar);
	index = line->index;
	if ((line->len + line->lprompt) < line->nb_col * line->nb_line)
	{
		tputs(tgetstr("sc", NULL), 1, ft_pchar);
		go_home(line);
		tputs(tgetstr("cr", NULL), 1, ft_pchar);
		tputs(tgetstr("cd", NULL), 1, ft_pchar);
		put_prompt(line->prompt, *line->ret);
		ft_putstr(line->curr->buff);
		tputs(tgetstr("rc", NULL), 1, ft_pchar);
		line->index = index;
	}
}

void		del_lines(t_line *line)
{
	size_t	index;
	int		line_pos;

	line_pos = get_cursor_line();
	index = line->index;
	tputs(tgetstr("vi", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	line->index < line->len
		? ft_putstr(&(line->curr->buff[line->index])) : ft_putstr("");
	line->index = line->len;
	while (line->index > index)
		get_to_left(line);
	if ((line->len + line->lprompt) % line->nb_col == 0
			&& line->index != line->len)
		deal_beg_line(line, line_pos);
	tputs(tgetstr("ve", NULL), 1, ft_pchar);
}
