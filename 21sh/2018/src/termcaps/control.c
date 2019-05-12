/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 04:46:41 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/29 12:39:05 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "put.h"
#include "shell.h"
#include "libft.h"
#include "shell_term.h"

void			deal_exit(t_line *line)
{
	if (line->curr->quoted)
	{
		line->shell_loop = 0;
		return ;
	}
	if (line->curr->buff[0])
		return ;
	term_restore(&line->save);
	line->shell_loop = 0;
}

static int		ft_cancel(t_line *line)
{
	go_end(line);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	init_new_buff(line);
	del_all_state(line);
	reset_hist(line);
	return (-1);
}

static void		cancel_on_completion(t_line *line)
{
	go_home(line);
	line->index = ft_strlen(line->curr->buff_tmp);
	line->len = line->index;
	tputs(tgetstr("cr", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	put_prompt(line->prompt, *line->ret);
	get_tmp_buff(&line->curr->buff, &line->curr->buff_tmp, 1);
	if (!line->curr->buff)
	{
		line->shell_loop = 0;
		return ;
	}
	ft_putstr(line->curr->buff);
	deal_reset(line->tree);
	line->tmp[0] = 3;
	line->index = line->len;
	if ((line->len + line->lprompt) % line->nb_col == 0)
	{
		tputs(tgetstr("do", NULL), 1, ft_pchar);
		tputs(tgetstr("cr", NULL), 1, ft_pchar);
	}
}

void			deal_cancel(t_line *line)
{
	if (*(line->e_cmpl) & COMPLETION)
		cancel_on_completion(line);
	else
	{
		if (line->tree[2])
			line->tree[2] = free_tree(line->tree[2]);
		line->tmp[0] = ft_cancel(line);
	}
	*(line->e_cmpl) &= ~COMPLETION;
	line->is_putb = 0;
}

void			ft_clear(t_line *line)
{
	tputs(tgetstr("cl", NULL), 1, ft_pchar);
	put_prompt(line->prompt, *line->ret);
	ft_putstr(line->curr->buff);
}
