/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 04:50:33 by rfontain          #+#    #+#             */
/*   Updated: 2019/04/27 16:05:56 by dbaffier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main_tools.h"
#include "put.h"
#include "shell.h"

void		set_signal(sig_t *signals)
{
	signals[SIGWINCH] = signal(SIGWINCH, sig_winch);
}

void		reset_signal(sig_t *signals)
{
	signal(SIGWINCH, signals[SIGWINCH]);
}

static void	deal_put_winch(t_line *line)
{
	size_t	index;

	index = line->index;
	go_home(line);
	tputs(tgetstr("cr", NULL), 1, ft_pchar);
	tputs(tgetstr("cd", NULL), 1, ft_pchar);
	put_prompt(line->prompt, *line->ret);
	ft_putstr(line->curr->buff);
	line->index = line->len;
	while (line->index > index)
		left_arrow(line);
	if ((line->index + line->lprompt) % line->nb_col == 0)
	{
		tputs(tgetstr("do", NULL), 1, ft_pchar);
		tputs(tgetstr("cr", NULL), 1, ft_pchar);
	}
	if (*line->e_cmpl & COMPLETION)
		get_complet(line);
}

void		sig_winch(int sig)
{
	t_line *line;

	(void)sig;
	line = get_struct();
	tgetent(NULL, line->term);
	line->nb_col = tgetnum("co");
	line->nb_line = tgetnum("li");
	line->key = WINCH;
	deal_put_winch(line);
}
