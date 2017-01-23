/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypad_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 03:22:30 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/23 20:22:35 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void		move_command(void)
{
	if (K_RIGHT && e.pos < ft_strlen(e.hist->cmd))
	{
		tputs(ft_tgetstr("nd"), 1, ft_pchar);
		e.pos++;
	}
	else if (K_LEFT && e.pos > 0)
	{
		tputs(ft_tgetstr("le"), 1, ft_pchar);
		e.pos--;
	}
}

static void		suppr_command(void)
{
	if (K_DEL)
	{
		ft_strcpy(e.hist->cmd + e.pos, e.hist->cmd + e.pos + 1);
		tputs(ft_tgetstr("dc"), 1, ft_pchar);
	}
	else if (K_SUPPR && e.pos > 0)
	{
		e.pos--;
		ft_strcpy(e.hist->cmd + e.pos, e.hist->cmd + e.pos + 1);
		tputs(ft_tgetstr("le"), 1, ft_pchar);
		tputs(ft_tgetstr("dc"), 1, ft_pchar);
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
	e.pos = 0;
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
