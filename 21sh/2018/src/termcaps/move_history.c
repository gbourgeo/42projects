/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 05:00:51 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/29 14:55:40 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"
#include "put.h"
#include "shell_term.h"

static int	find_hist(t_line *line, int way)
{
	size_t	len;

	len = ft_strlen(line->curr->buff_tmp);
	while (line->hist)
	{
		if (line->hist->c_size > len && line->hist->c_size < MALLOC_MAX)
			if (ft_strstr(line->hist->content, line->curr->buff_tmp)
					== line->hist->content && (line->hist->tmp
						? ft_strcmp(line->curr->buff, line->hist->tmp)
						: ft_strcmp(line->curr->buff, line->hist->content))
						!= 0)
				return (1);
		if (!(way == 1 ? line->hist->prev : line->hist->next))
			return (2);
		line->hist = (way == 1 ? line->hist->prev : line->hist->next);
	}
	return (0);
}

static int	key_complet(t_line *line, int key)
{
	if (*line->e_cmpl & COMPLETION && line->is_putb)
	{
		line->key = key;
		get_complet(line);
		return (1);
	}
	else if (*line->e_cmpl & COMPLETION)
	{
		free(line->curr->buff_tmp);
		line->curr->buff_tmp = NULL;
		*line->e_cmpl &= ~COMPLETION;
	}
	return (0);
}

static void	is_find(t_line *line, int find, int way, t_hist *tmp)
{
	if (find == 1)
	{
		if (line->hist->tmp)
			get_tmp_buff(&line->curr->buff, &line->hist->tmp, 0);
		else
			get_tmp_buff(&line->curr->buff, &line->hist->content, 0);
		if (!line->curr->buff)
			line->shell_loop = 0;
		if (line->curr->buff)
			put_new_prompt(line);
	}
	else if (find == 2 && way == 1)
	{
		get_tmp_buff(&line->curr->buff, &line->curr->buff_tmp, 1);
		put_new_prompt(line);
	}
	else if (way == 0)
	{
		line->hist = tmp;
		if (!tmp->prev && ft_strcmp(line->curr->buff, tmp->content))
		{
			free(line->curr->buff_tmp);
			line->curr->buff_tmp = NULL;
		}
	}
}

void		up_arrow(t_line *line)
{
	int		find;
	t_hist	*tmp;

	if (key_complet(line, UP) || !line->hist)
		return ;
	if (!line->curr->buff_tmp)
		line->curr->buff_tmp = ft_strdup(line->curr->buff);
	else
	{
		if (line->hist && ft_strcmp(line->hist->content, line->curr->buff))
		{
			if (line->hist->tmp)
				free(line->hist->tmp);
			line->hist->tmp = ft_strdup(line->curr->buff);
		}
	}
	tmp = line->hist;
	find = find_hist(line, 0);
	is_find(line, find, 0, tmp);
}

void		down_arrow(t_line *line)
{
	int		find;

	find = 0;
	if (key_complet(line, DOWN))
		return ;
	if (!line->curr->buff_tmp)
		return ;
	if (line->hist && ft_strcmp(line->hist->content, line->curr->buff))
	{
		if (line->hist->tmp)
			free(line->hist->tmp);
		line->hist->tmp = ft_strdup(line->curr->buff);
	}
	find = find_hist(line, 1);
	is_find(line, find, 1, NULL);
}
