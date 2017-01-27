/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypad_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 03:22:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/27 02:30:43 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		move_command(void)
{
	if (K_RIGHT && (size_t)e.pos.x < ft_strlen(e.hist->cmd))
	{
		ft_pos(1);
//		e.pos.x++;
	}
	else if (K_LEFT && e.pos.x > 0)
	{
		ft_pos(-1);
//		e.pos.x--;
	}
}

static void		suppr_command(void)
{
	size_t		x;

	if (K_DEL && e.hist->cmd[e.pos.x])
	{
		ft_strcpy(e.hist->cmd + e.pos.x, e.hist->cmd + e.pos.x + 1);
		tputs(ft_tgetstr("cd"), 1, ft_pchar);
		ft_putstr_fd(&e.hist->cmd[e.pos.x], e.fd);
		x = ft_strlen(&e.hist->cmd[e.pos.x]);
		e.pos.x += x;
		ft_pos(-x);
	}
	else if (K_SUPPR && e.pos.x > 0)
	{
		ft_pos(-1);
//		e.pos.x--;
		ft_strcpy(&e.hist->cmd[e.pos.x], &e.hist->cmd[e.pos.x + 1]);
		tputs(ft_tgetstr("cd"), 1, ft_pchar);
		ft_putstr_fd(&e.hist->cmd[e.pos.x], e.fd);
		x = ft_strlen(&e.hist->cmd[e.pos.x]);
		e.pos.x += x;
		ft_pos(-x);
	}
}

static void		ctrl_c(void)
{
	rewrite_command();
	if (*e.hist->cmd && e.hist->next == NULL)
		ft_bzero(e.hist->cmd, e.hist->cmd_size);
	while (e.hist->next)
		e.hist = e.hist->next;
	if (*e.hist->cmd && (e.hist = new_hist()) == NULL)
		ft_exit_all("Malloc failed.");
	if (e.hist->prev)
		e.hist->prev->next = e.hist;
	write(e.fd, "\n", 1);
	e.pos.x = 0;
	e.pos.y = 0;
	prompt(e.env);
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
}
