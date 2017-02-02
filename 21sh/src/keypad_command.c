/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypad_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 03:22:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/02/02 22:56:37 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
** "sc"		Save cursor position.
** "cd"		Clear the line the cursor is on, and all the lines below it,
**			down to the bottom of the screen.
** "rc"		Restore cursor position.
*/

static void		move_command(void)
{
	if (K_RIGHT && (size_t)e.pos < ft_strlen(e.hist->cmd))
		ft_pos(1);
	else if (K_LEFT && e.pos > 0)
		ft_pos(-1);
}

static void		suppr_command(void)
{
	if (K_DEL && e.hist->cmd[e.pos])
	{
		ft_strcpy(e.hist->cmd + e.pos, e.hist->cmd + e.pos + 1);
		tputs(ft_tgetstr("sc"), 1, ft_pchar);
		tputs(ft_tgetstr("cd"), 1, ft_pchar);
		ft_putstr_fd(&e.hist->cmd[e.pos], e.fd);
		tputs(ft_tgetstr("rc"), 1, ft_pchar);
	}
	else if (K_SUPPR && e.pos > 0)
	{
		ft_pos(-1);
		ft_strcpy(&e.hist->cmd[e.pos], &e.hist->cmd[e.pos + 1]);
		tputs(ft_tgetstr("sc"), 1, ft_pchar);
		tputs(ft_tgetstr("cd"), 1, ft_pchar);
		ft_putstr_fd(&e.hist->cmd[e.pos], e.fd);
		tputs(ft_tgetstr("rc"), 1, ft_pchar);
	}
}

static void		goto_eol(void)
{
	char		*str;
	t_pos		pos;

	pos.x = e.cursor.x + ft_strlen(&e.hist->cmd[e.pos]);
	pos.y = e.cursor.y;
	while (pos.x >= e.sz.ws_col)
	{
		pos.x -= e.sz.ws_col;
		pos.y++;
	}
	str = tgoto(ft_tgetstr("cm"), pos.x, pos.y);
	tputs(str, 1, ft_pchar);
}

static void		ctrl_c(void)
{
	rewrite_command();
	goto_eol();
	write(e.fd, "\n", 1);
	hist_clean();
	while (e.hist->prev)
		e.hist = e.hist->prev;
	ft_bzero(e.hist->cmd, e.hist->cmd_size);
	e.pos = 0;
	prompt(e.env);
	cursor_position(&e.origin);
	ft_memcpy(&e.cursor, &e.origin, sizeof(e.cursor));
}

void			keypad_command(void)
{
	if (K_UP || K_DOWN)
		historic_command();
	else if (K_RIGHT || K_LEFT)
		move_command();
	else if (K_DEL || K_SUPPR)
		suppr_command();
	else if (SHFT_KEY)
		shift_command();
	else if (CTRL_KEY)
		ctrl_command();
	else if (CT_SH_KEY)
		ctrl_shift_command();
	else if (CTRL_C)
		ctrl_c();
	else if (K_HOME)
		k_home();
	else if (K_END)
		k_end();
}
