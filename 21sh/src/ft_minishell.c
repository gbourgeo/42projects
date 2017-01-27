/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbourgeo <gbourgeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/28 04:47:21 by gbourgeo          #+#    #+#             */
/*   Updated: 2017/01/27 02:27:11 by gbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

static void		treat_command(void)
{
	char		**args;

	rewrite_command();
	write(e.fd, "\n", 1);
	e.pos.x = 0;
	e.pos.y = 0;
	if (*e.hist->cmd)
	{
		args = ft_split_whitespaces(e.hist->cmd);
		if (args == NULL)
			ft_exit_all("Can't parse your command.");
		restore_term();
		check_and_exec(args, e.env);
		redefine_term();
		if ((e.hist = new_hist()) == NULL)
			ft_exit_all("Malloc failed.");
		if (e.hist->prev)
			e.hist->prev->next = e.hist;
	}
	if (e.hist->prev)
		ft_putendl(e.hist->prev->cmd);
	prompt(e.env);
}

void			ft_shell(void)
{
	int			len;

	prompt(e.env);
	while ((len = read(e.fd, e.buf, READ_SIZE)) > 0)
	{
//		printf("%d %d %d %d %d %d %d %d\n", e.buf[0], e.buf[1], e.buf[2], e.buf[3], e.buf[4], e.buf[5], e.buf[6], e.buf[7]);
		if (K_PRINT)
			read_command(len);
		else if (ENTER)
			treat_command();
		else if (KEYPAD || K_SUPPR || CTRL_C)
			keypad_command();
		else if (COPY_KEY)
			copy_command();
		else if (CTRL_D && !*e.hist->cmd)
			break ;
		if (!SHFT_KEY && !CT_SH_KEY && e.cpy.cpy != 0)
			rewrite_command();
		if (e.origin.y == e.sz.ws_row && e.origin.x + e.pos.x > e.sz.ws_col)
			e.pos.y = (e.origin.x + e.pos.x) / e.sz.ws_col;
		ft_memset(e.buf, 0, len);
	}
}

void			rewrite_command(void)
{
	int			i;
	int			y;

	i = ft_strlen(e.hist->cmd);
	if (i)
	{
		tputs(ft_tgetstr("rc"), 1, ft_pchar);
		y = e.pos.y;
		while (y--)
			tputs(ft_tgetstr("up"), 1, ft_pchar);
		tputs(ft_tgetstr("cd"), 1, ft_pchar);
		write(e.fd, e.hist->cmd, i);
		y = e.pos.x;
		e.pos.x = i;
		ft_pos(-(i - y));
	}
	e.cpy.cpy = 0;
}
