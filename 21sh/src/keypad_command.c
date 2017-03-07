/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypad_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 03:22:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/03/07 16:24:29 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
** "sc"		Save cursor position.
** "cd"		Clear the line the cursor is on, and all the lines below it,
**			down to the bottom of the screen.
** "rc"		Restore cursor position.
**
** "sf"		Scroll the screen one line up if cursor at the end of the screen or
**			Move the cursor one line down.
** "cr"		Move the cursor at the begining of the line it is on.
*/

static void		move_command(t_env *e)
{
	if (K_RIGHT(e) && e->pos < e->hist->cmd_len)
		ft_pos(1, e);
	else if (K_LEFT(e) && e->pos > e->q_pos)
		ft_pos(-1, e);
}

static void		suppr_command(t_env *e)
{
	if (K_DEL(e) && e->hist->cmd[e->pos])
	{
		e->hist->cmd_len--;
		if (e->hist->cmd[e->pos] == e->quote)
			e->quote = 0;
		ft_strcpy(e->hist->cmd + e->pos, e->hist->cmd + e->pos + 1);
		rewrite_command(e);
	}
	else if (K_SUPPR(e) && e->pos > e->q_pos)
	{
		ft_pos(-1, e);
		e->hist->cmd_len--;
		if (e->hist->cmd[e->pos] == e->quote)
			e->quote = 0;
		ft_strcpy(&e->hist->cmd[e->pos], &e->hist->cmd[e->pos + 1]);
		rewrite_command(e);
	}
}

static void		ctrl_c(t_env *e)
{
	rewrite_command(e);
	hist_clean(e->hist);
	e->cmd = e->hist;
	hist_add(e, NULL);
	tputs(ft_tgetstr("sf"), 1, ft_pchar);
	tputs(ft_tgetstr("cr"), 1, ft_pchar);
	e->quote = 0;
	prompt(e);
}

void			keypad_command(t_env *e)
{
	if (K_UP(e) || K_DOWN(e))
		historic_command(e);
	else if (K_RIGHT(e) || K_LEFT(e))
		move_command(e);
	else if (K_DEL(e) || K_SUPPR(e))
		suppr_command(e);
	else if (SHFT_KEY(e))
		shift_command(e);
	else if (CTRL_KEY(e))
		ctrl_command(e);
	else if (CT_SH_KEY(e))
		ctrl_shift_command(e);
	else if (CTRL_C(e))
		ctrl_c(e);
	else if (K_HOME(e))
		k_home(e);
	else if (K_END(e))
		k_end(e);
}
