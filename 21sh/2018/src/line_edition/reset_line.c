/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 03:41:00 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/26 16:59:38 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell_term.h"
#include "libft.h"
#include "shell.h"

void	put_new_prompt(t_line *line)
{
	go_home(line);
	tputs(tgetstr("cr", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	put_prompt(line->prompt, *line->ret);
	ft_putstr(line->curr->buff);
	line->index = ft_strlen(line->curr->buff);
	line->len = line->index;
	if ((line->index + line->lprompt) % line->nb_col == 0)
	{
		tputs(tgetstr("do", NULL), 1, ft_pchar);
		tputs(tgetstr("cr", NULL), 1, ft_pchar);
	}
}

void	del_all_state(t_line *line)
{
	int i;

	i = 0;
	while (i < 10)
	{
		*(line->e_cmpl) &= ~(1 << i);
		i++;
	}
	line->is_putb = 0;
}

void	reset_hist(t_line *line)
{
	if (!line->hist)
		return ;
	line->hist = line->hist->begin;
	while (line->hist->next)
	{
		if (line->hist->tmp)
			free(line->hist->tmp);
		line->hist->tmp = NULL;
		if (line->hist->prev)
			line->hist->begin = line->hist->prev->begin;
		line->hist = line->hist->next;
	}
	if (line->hist->tmp)
		free(line->hist->tmp);
	line->hist->tmp = NULL;
	if (line->hist->prev)
		line->hist->begin = line->hist->prev->begin;
	line->hist = line->hist->begin;
}
