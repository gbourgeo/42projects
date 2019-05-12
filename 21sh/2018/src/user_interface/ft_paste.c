/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paste.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 05:59:37 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/02 16:37:28 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "shell_term.h"

static int	get_paste(t_line *line, int *j)
{
	char	c;
	char	tmp;
	int		i;

	i = 0;
	if (line->index > MAX_SHELL_LEN)
		return (1);
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

void		ft_paste(t_line *line)
{
	int		index_tmp;
	int		j;
	int		len;

	if (!line->copy)
		return ;
	j = 0;
	index_tmp = line->index;
	if (*line->e_cmpl & COMPLETION)
		erase_completion(line, index_tmp);
	*line->e_cmpl &= ~COMPLETION;
	if (line->len + (len = ft_strlen(line->copy)) > MAX_SHELL_LEN)
		return ;
	while (line->copy[j])
		if (get_paste(line, &j))
			break ;
	line->len += len;
	ft_putstr(&line->curr->buff[index_tmp]);
	if (line->index != line->len)
	{
		j = line->index;
		line->index = line->len;
		while ((int)line->index > j)
			left_arrow(line);
	}
}
