/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 08:44:05 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/21 22:37:22 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "libft.h"
#include "shell.h"

t_line			*get_struct(void)
{
	static t_line	*line = NULL;

	if (!line)
		line = ft_memalloc(sizeof(t_line));
	return (line);
}

void			free_buff(t_line *line)
{
	if (!line->curr)
		return ;
	if (line->curr->buff_tmp)
		free(line->curr->buff_tmp);
	if (line->curr->buff)
		free(line->curr->buff);
	free(line->curr);
}

static void		free_hist(t_hist *hist)
{
	if (!hist)
		return ;
	if (hist)
		free_hist(hist->next);
	if (hist->tmp)
		free(hist->tmp);
	free(hist->content);
	free(hist);
}

void			free_struct(t_line *line)
{
	if (!line)
		return ;
	free_all_tree(line);
	free_buff(line);
	while (line->hist && line->hist->prev)
		line->hist = line->hist->prev;
	free_hist(line->hist);
	free(line->e_cmpl);
	free(line->prompt);
	if (line->copy)
		free(line->copy);
	free(line);
}
