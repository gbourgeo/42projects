/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 01:38:48 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/22 20:32:54 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "put.h"
#include "shell_lib.h"
#include "shell_term.h"
#include "shell.h"

static void	put_cpl_screen(t_line *line, int nb_ret)
{
	int		iter;

	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	line->len = ft_strlen(line->curr->buff);
	line->index = line->len;
	iter = line->len + line->lprompt;
	while (nb_ret--)
		tputs(tgetstr("up", NULL), 1, ft_pchar);
	while (iter >= 0)
	{
		tputs(tgetstr("up", NULL), 1, ft_pchar);
		iter -= line->nb_col;
	}
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_pchar);
	put_prompt(line->prompt, *line->ret);
	ft_putstr(line->curr->buff);
	if ((line->len + line->lprompt) % line->nb_col == 0)
	{
		tputs(tgetstr("do", NULL), 1, ft_pchar);
		tputs(tgetstr("cr", NULL), 1, ft_pchar);
	}
}

static int	deal_unfind(t_line *line)
{
	int		tmp_len;

	tmp_len = ft_strlen(line->curr->buff) + line->lprompt;
	write(2, "\a", 1);
	free(line->curr->buff_tmp);
	line->curr->buff_tmp = NULL;
	line->is_putb = 0;
	line->tmp[0] = 0;
	while (tmp_len >= 0)
	{
		tputs(tgetstr("up", NULL), 1, ft_pchar);
		tmp_len -= line->nb_col;
	}
	put_prompt(line->prompt, *line->ret);
	ft_putstr(line->curr->buff);
	if ((line->len + line->lprompt) % line->nb_col == 0)
	{
		tputs(tgetstr("do", NULL), 1, ft_pchar);
		tputs(tgetstr("cr", NULL), 1, ft_pchar);
	}
	return (1);
}

static int	deal_ret(t_tree *file, t_line *line, int *nb_ret, int put)
{
	if ((put = put_complet(file, &put, line, nb_ret)) == 1)
	{
		*line->e_cmpl |= COMPLETION;
		line->tmp[0] = 10;
	}
	else if (put == -1)
		return (deal_unfind(line));
	return (0);
}

void		deal_complet(t_tree *file, t_line *line)
{
	int		nb_ret;

	nb_ret = 0;
	go_home(line);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	go_end(line);
	tputs(tgetstr("do", NULL), 1, ft_pchar);
	tputs(tgoto(tgetstr("ch", NULL), 0, 0), 1, ft_pchar);
	if (!line->curr->buff_tmp)
	{
		line->curr->buff_tmp = ft_strdup(line->curr->buff);
		if (deal_ret(file, line, &nb_ret, 0))
			return ;
	}
	else
	{
		if (deal_ret(file, line, &nb_ret, 1))
			return ;
	}
	put_cpl_screen(line, nb_ret);
}
