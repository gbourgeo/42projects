/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 16:59:39 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/29 01:36:10 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "shell_term.h"
#include "libft.h"

int			get_cursor_line(void)
{
	static char	cmd[] = "\033[6n";
	char		buf[15];
	int			nb_read;
	char		*ptr;

	ft_memset(buf, 0, sizeof(buf));
	write(STDIN_FILENO, cmd, sizeof(cmd));
	if ((nb_read = read(STDIN_FILENO, buf, sizeof(buf) - 1)) < 0)
		return (0);
	buf[nb_read] = 0;
	if (!(ptr = ft_strchr(buf, '[')))
		return (0);
	ptr++;
	return (ft_atoi(ptr));
}

static void	ft_putbuff_len(t_line *line)
{
	int		i;

	i = line->index;
	while ((i + line->lprompt) % line->nb_col != 0 && i > 0)
		i--;
	write(0, &line->curr->buff[i], line->nb_col);
}

void		deal_scroll(t_line *line, int up, int nb_line)
{
	if (get_cursor_line() == nb_line)
	{
		tputs(tgetstr(up ? "sr" : "sf", NULL), 1, ft_pchar);
		tputs(tgetstr("sc", NULL), 1, ft_pchar);
		tputs(tgetstr("cr", NULL), 1, ft_pchar);
		if (up && line->index + line->lprompt < line->nb_col)
		{
			put_prompt(line->prompt, *line->ret);
		}
		ft_putbuff_len(line);
		tputs(tgetstr("rc", NULL), 1, ft_pchar);
	}
	else
		tputs(tgetstr(up ? "up" : "do", NULL), 1, ft_pchar);
}

void		mv_line_up(t_line *line)
{
	if ((int)line->index - (int)line->nb_col >= 0)
	{
		line->index -= line->nb_col;
		deal_scroll(line, 1, 1);
		tputs(tgoto(tgetstr("ch", NULL), 0,
				(line->index + line->lprompt) % line->nb_col), 1, ft_pchar);
	}
}

void		mv_line_down(t_line *line)
{
	if (line->index + line->nb_col <= line->len)
	{
		line->index += line->nb_col;
		deal_scroll(line, 0, (int)line->nb_line);
		tputs(tgoto(tgetstr("ch", NULL), 0,
				(line->index + line->lprompt) % line->nb_col), 1, ft_pchar);
	}
}
