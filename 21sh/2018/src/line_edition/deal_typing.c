/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_typing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 08:55:32 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/25 23:40:17 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "main_tools.h"
#include "put.h"

static void	deal_return(t_line *line, int goal)
{
	ft_putstr(&line->curr->buff[line->index]);
	if ((line->len + line->lprompt) % line->nb_col == 0)
		tputs(tgetstr("do", NULL), 1, ft_pchar);
	line->index = line->len;
	while ((int)line->index > goal)
	{
		line->key = LEFT;
		if ((int)line->index - goal > (int)line->nb_col)
			mv_line_up(line);
		else
			left_arrow(line);
	}
}

static void	deal_unselect(t_line *line)
{
	int		tmp;
	int		i;

	if ((size_t)line->slct_beg == line->index)
	{
		tputs(tgetstr("cd", NULL), 1, ft_pchar);
		i = (int)line->index;
		deal_return(line, line->index);
		tputs(tgoto(tgetstr("ch", NULL), 0, (line->index
						+ line->lprompt) % line->nb_col), 1, ft_pchar);
	}
	else
	{
		tmp = line->index;
		i = line->slct_end - line->slct_beg + 1;
		while (--i)
			left_arrow(line);
		deal_return(line, tmp);
		if ((line->index + line->lprompt) % line->nb_col == 0)
			tputs(tgetstr("do", NULL), 1, ft_pchar);
	}
}

int			get_buff_realloc(t_line *line, int nb_read)
{
	char	*tmp;
	size_t	max_len;

	max_len = MAX_SHELL_LEN;
	tmp = ft_strdup(line->curr->buff);
	free(line->curr->buff);
	if (!(line->curr->buff = ft_memalloc(sizeof(char)
					* (max_len * ((line->len + nb_read) / max_len + 1)) + 1)))
	{
		free(tmp);
		line->shell_loop = 0;
		return (1);
	}
	ft_strcpy(line->curr->buff, tmp);
	free(tmp);
	return (0);
}

static void	get_read(t_line *line, int *nb_read)
{
	if ((line->len % MAX_SHELL_LEN) > ((*nb_read = read(0, line->tmp, 10)) +
			line->len) % MAX_SHELL_LEN
				&& line->len + *nb_read < MALLOC_MAX)
	{
		if (get_buff_realloc(line, *nb_read))
			return ;
	}
	if (line->len + *nb_read < MALLOC_MAX)
		get_typing(line, *nb_read);
	if (ft_strncmp(line->tmp, "\x1B\x5B\x31\x3B\x32", 5) != 0)
	{
		if (line->slct_beg > -1)
			deal_unselect(line);
		if (ft_strcmp(line->tmp, "\xE2\x89\x88") != 0
				&& ft_strcmp(line->tmp, "\xC3\xA7") != 0)
		{
			line->slct_beg = -1;
			line->slct_end = -1;
		}
	}
}

void		deal_typing(t_line *line)
{
	int		nb_read;

	nb_read = 0;
	ft_bzero(line->tmp, 10);
	while ((line->tmp[0] != 10 && line->tmp[0] != -1)
			|| *(line->e_cmpl) & COMPLETION)
	{
		ft_bzero(line->tmp, 10);
		get_read(line, &nb_read);
		line->tmp[nb_read] = '\0';
		if (line->tmp[0] == '/')
			line->tree[2] = free_tree(line->tree[2]);
		else if (!(*line->e_cmpl & COMPLETION))
			deal_reset(line->tree);
		if (line->key)
			line->key = 0;
		deal_key(line);
		if (!line->shell_loop)
			break ;
		if (*(line->e_cmpl) & COMPLETION && line->tmp[0] == 10)
			set_complet(line, 1);
	}
}
