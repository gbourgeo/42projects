/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 11:37:00 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/25 22:12:51 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "shell_term.h"

static void	cut_on_buff(t_line *line, int beg, int end)
{
	while (line->curr->buff[beg])
	{
		if (line->curr->buff[end])
			line->curr->buff[beg] = line->curr->buff[end++];
		else
			line->curr->buff[beg] = '\0';
		beg++;
	}
	if (line->slct_end == (int)line->index)
	{
		while (line->slct_end != line->slct_beg)
		{
			left_arrow(line);
			line->slct_end -= 1;
		}
	}
}

void		ft_cut(t_line *line)
{
	int beg;
	int end;

	if (line->slct_beg < 0)
		return ;
	beg = line->slct_beg;
	end = line->slct_end;
	ft_copy(line);
	cut_on_buff(line, beg, end);
	line->len = ft_strlen(line->curr->buff);
	line->slct_end = -1;
	line->slct_beg = -1;
	tputs(tgetstr("sc", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	ft_putstr(&line->curr->buff[line->index]);
	tputs(tgetstr("rc", NULL), 1, ft_pchar);
}
