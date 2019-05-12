/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paste.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 05:59:37 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/25 23:20:33 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "shell_term.h"

static int	get_paste(t_line *line, int *j)
{
	char	c;
	char	tmp;
	size_t	i;

	i = 0;
	tmp = line->curr->buff[line->index + 1];
	line->curr->buff[line->index + 1] = line->curr->buff[line->index];
	line->curr->buff[line->index] = line->copy[*j];
	i = line->index + 1;
	while (line->curr->buff[i])
	{
		c = line->curr->buff[i + 1];
		line->curr->buff[i + 1] = tmp;
		tmp = c;
		i++;
	}
	*j += 1;
	line->index++;
	return (0);
}

static void	erase_completion(t_line *line, int index_tmp)
{
	tputs(tgetstr("sc", NULL), 1, ft_pchar);
	go_end(line);
	tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgetstr("cr", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	tputs(tgetstr("rc", NULL), 1, ft_pchar);
	line->index = index_tmp;
}

static void	handle_index(t_line *line)
{
	int		j;

	j = line->index;
	line->index = line->len;
	while ((int)line->index > j)
		left_arrow(line);
	if (line->index == line->len
			&& (line->len + line->lprompt) % line->nb_col == 0)
	{
		tputs(tgetstr("do", NULL), 1, ft_pchar);
		tputs(tgetstr("cd", NULL), 1, ft_pchar);
	}
}

void		ft_paste(t_line *line)
{
	int		index_tmp;
	int		j;
	int		len;

	if (!line->copy || line->len + (len = ft_strlen(line->copy)) > MALLOC_MAX)
		return ;
	j = 0;
	index_tmp = line->index;
	if (*line->e_cmpl & COMPLETION)
		erase_completion(line, index_tmp);
	*line->e_cmpl &= ~COMPLETION;
	if ((line->len / MAX_SHELL_LEN) < (line->len + len) / MAX_SHELL_LEN)
		if (get_buff_realloc(line, len))
			return ;
	while (line->copy[j])
		if (get_paste(line, &j))
			break ;
	line->len += len;
	ft_putstr(&line->curr->buff[index_tmp]);
	handle_index(line);
}
