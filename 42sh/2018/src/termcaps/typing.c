/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 04:57:17 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/29 21:50:09 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "shell_term.h"
#include "put.h"
#include "libft.h"

static void	ft_putbuff_len(t_line *line)
{
	int		i;

	i = line->index;
	while ((i + line->lprompt) % line->nb_col != 0 && i > 0)
		i--;
	write(0, &line->curr->buff[i - line->nb_col + line->lprompt], line->nb_col);
}

static void	get_to_left(t_line *line)
{
	if (line->index > 0)
		line->index -= 1;
	else
		write(2, "\a", 1);
	if (line->index
			&& (line->index + line->lprompt) % line->nb_col == 0)
	{
		if (get_cursor_line() == 1)
		{
			tputs(tgetstr("sr", NULL), 1, ft_pchar);
			tputs(tgetstr("cr", NULL), 1, ft_pchar);
			if (line->index + line->lprompt <= line->nb_col)
				put_prompt(line->prompt, *line->ret);
			ft_putbuff_len(line);
		}
		tputs(tgetstr("up", NULL), 1, ft_pchar);
	}
	tputs(tgoto(tgetstr("ch", NULL), 0,
				(line->index + line->lprompt) % line->nb_col), 1, ft_pchar);
}

static void	get_to_len(t_line *line, char tchar)
{
	char	cbis;
	int		j;

	j = 1;
	while (line->index + j < line->len)
	{
		cbis = line->curr->buff[line->index + j];
		line->curr->buff[line->index + j] = tchar;
		tchar = cbis;
		j++;
	}
	j = (int)line->index;
	ft_putstr_fd(&(line->curr->buff[line->index]), 0);
	line->index = line->len;
	while ((int)line->index > j)
	{
		if ((int)line->index - j > (int)line->nb_col)
			mv_line_up(line);
		else
			get_to_left(line);
	}
}

static void	get_to_buff(t_line *line, int *cp)
{
	char	tchar;

	tchar = line->curr->buff[line->index + 1];
	if (line->index != line->len)
		line->curr->buff[line->index + 1] = line->curr->buff[line->index];
	line->curr->buff[line->index++] = line->tmp[*cp];
	line->len++;
	ft_putchar_fd(line->tmp[*cp], 0);
	*cp += 1;
	if (line->index != line->len)
		get_to_len(line, tchar);
	line->curr->buff[line->len] = '\0';
	if ((line->index + line->lprompt) % line->nb_col == 0)
	{
		tputs(tgetstr("do", NULL), 1, ft_pchar);
		tputs(tgetstr("cr", NULL), 1, ft_pchar);
	}
}

void		get_typing(t_line *line, int nb_read)
{
	int		cp;

	cp = 0;
	line->tmp[nb_read] = '\0';
	if (ft_isprint(line->tmp[0]) && *line->e_cmpl & COMPLETION)
	{
		if (line->is_putb == 1)
			set_complet(line, 0);
		else
		{
			line->is_putb -= 1;
			free(line->curr->buff_tmp);
			line->curr->buff_tmp = NULL;
			*line->e_cmpl &= ~COMPLETION;
			line->index = line->len;
		}
	}
	if (line->tmp[0] == 11)
		return ;
	while (cp < nb_read && line->tmp[0] != 12 && (ft_isprint(line->tmp[cp])
				|| ft_isspace(line->tmp[cp]))
			&& line->tmp[0] != 9 && line->tmp[cp] != 10)
		get_to_buff(line, &cp);
}
